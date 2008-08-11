#include <QUrl>
#include <QTimer>
#include <QList>
#include <QWidget>
#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>

#include "htmlChatView.h"


HTMLChatView::HTMLChatView(QWidget * parent, HTMLChatTheme _theme, IconServer* iconServer)
: ChatView(parent), theme(_theme), isReady(false), queuedTheme(0), queuedClear(false) {

    webView.setParent(this);

    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(&webView);

    setLayout(layout);
    setFocusPolicy(Qt::NoFocus);
    webView.setFocusPolicy(Qt::NoFocus);
    webView.setContextMenuPolicy(Qt::NoContextMenu);

    networkManager = new NetworkAccessManager(0, iconServer);
    webView.page()->setNetworkAccessManager(networkManager);

    webView.page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    webView.setMinimumSize(100, 100);
    setMinimumSize(100, 100);

    connect(webView.page(), SIGNAL(linkClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));
    connect(webView.page(), SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));

}


void HTMLChatView::clear() {
    if (isReady) {
        appendedEvents.clear();
        evaluateJS("psi_clearMessages()");
    }
    else {
        qDebug() << "queued clear()";
        queuedClear = true;
    }
}


void HTMLChatView::init() {

    connect(&webView, SIGNAL(loadFinished(bool)), this, SLOT(onEmptyDocumentLoaded(bool)));
    connect(&jsNotifier, SIGNAL(onInitFinished()), this, SLOT(onInitDocumentFinished()));
    connect(&jsNotifier, SIGNAL(onAppendFinished()), this, SLOT(onAppendFinished()));

    webView.setHtml(createEmptyDocument(theme.baseHref(), theme.currentVariant()), theme.baseHref());
    //rest in onEmptyDocumentLoaded
}


void HTMLChatView::onEmptyDocumentLoaded(bool ok) {
    if (!ok) {
        qDebug() << "WARNING: HTMLChatView::onEmptyDocumentLoaded() - load failed";
        //NOTE: if ok is false, then:
        //NOTE: a) there was HTTP error - doesn't apply here, because empty document is loaded from string
        //NOTE: b) someone deleted QWebView (destructor was called) while it was loading page - 
        //NOTE: either it's programmer fault or someone close psi exactly when webkit was loading empty page

        return;
    }

    HTMLChatPart header = theme.headerTemplate().createFreshHTMLPart();
    HTMLChatPart footer = theme.footerTemplate().createFreshHTMLPart();

    theme.fillPartWithThemeKeywords(header, chatInfo());
    theme.fillPartWithThemeKeywords(footer, chatInfo());

    QString headerStr = header.toString();
    QString footerStr = footer.toString();

    escapeString(headerStr);
    escapeString(footerStr);

    importJSChatFunctions();

    webView.page()->mainFrame()->addToJavaScriptWindowObject("jsNotifier", &jsNotifier);

    evaluateJS("psi_initDocument(\"" + headerStr + "\", \"" + footerStr + "\")");
    //rest in onInitDocumentFinished
}


void HTMLChatView::onInitDocumentFinished() {

    isReady = true;

    if (queuedTheme) {
        qDebug() << "changing queued theme" << queuedTheme->baseHref();
        setTheme(*queuedTheme);
        delete queuedTheme;
        queuedTheme = 0;
    }

    reappendEvents();

    if (queuedClear) {
        queuedClear = false;
        clear();
    }

    emit initDocumentFinished();
}


void HTMLChatView::onAppendFinished() {
    if (atBottom()) {
        QTimer::singleShot(0, this, SLOT(onDoScrolling()));
    }
}


void HTMLChatView::onDoScrolling() {
    scrollToBottom();
    emit appendFinished();
}


void HTMLChatView::onLinkClicked(const QUrl& url) {
    emit openURL(url.toString());
}


QString HTMLChatView::createEmptyDocument(QString baseHref, QString themeVariant) {
    return QString(
                   "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
                   "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">"
                   "<html xmlns=\"http://www.w3.org/1999/xhtml\">"
                   "        <head>"
                   "                <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />"
                   "                <base href=\"%1\"/>"
                   "                <style id=\"baseStyle\" type=\"text/css\" media=\"screen,print\">"
                   "                        @import url(\"main.css\");"
                   "                        @import url(\"%2\");"
                   "                        *{ word-wrap:break-word; }"
                   "                </style>"
                   "        </head>"
                   "        <body></body>"
                   "</html>").arg(baseHref).arg("Variants/" + QString(themeVariant) + ".css");

}


void HTMLChatView::appendMessage(const MessageChatEvent *msg, bool alreadyAppended) {
    ChatView::appendMessage(msg, alreadyAppended);

    if (isReady) { // we dont want to append events before init was finished
        // events will be appended in reappendEvents (called from onInitDpcumentFinished)

        QString part;

        if (msg->isLocal())
            part = theme.createOutgoingMessagePart(msg);
        else
            part = theme.createIncomingMessagePart(msg);

        escapeString(part);

        if (msg->isConsecutive()) {
            evaluateJS("psi_appendConsecutiveMessage(\"" + part + "\", \"" +
                       escapeStringCopy(msg->body()) + "\"" + ")");
        }
        else {
            evaluateJS("psi_appendNextMessage(\"" + part + "\", \"" +
                       escapeStringCopy(msg->body()) + "\"" + ")");
        }
    }
    else {
        qDebug() << " -- appendMessage queued";
    }
}


void HTMLChatView::appendEvent(const ChatEvent* event, bool alreadyAppended) {
    ChatView::appendEvent(event, alreadyAppended);

    if (isReady) { // we dont want to append events before init was finished
        // events will be appended in reappendEvents (called from onInitDpcumentFinished)


        QString part = event->getRightTemplateAndFillItWithData(theme);
        escapeString(part);

        evaluateJS("psi_appendEvent(\"" + part + "\")");
    }
    else {
        qDebug() << " -- appendEvent queued";
    }
}


void HTMLChatView::evaluateJS(QString scriptSource) {
    webView.page()->mainFrame()->evaluateJavaScript(scriptSource);
    //qDebug() << "HTMLChatView::evaluateJS(" << scriptSource << ")\n";
}


void HTMLChatView::importJSChatFunctions() {
    QFile file(":/htmlChatView.js");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "WARNING: HTMLChaTView::importJSChatFunction() - loading Qt Resource failed";
        //NOTE: I (senu) assume that reading from Qt Resource always succeed - there's no error handling
    }

    QString jsCode = file.readAll();
    evaluateJS(jsCode);

}


HTMLChatView::~HTMLChatView() {
    qDebug() << dumpContent();
    delete queuedTheme;
    delete networkManager;
}


QString HTMLChatView::dumpContent() {
    return webView.page()->mainFrame()->toHtml();
}


void HTMLChatView::escapeString(QString& str) {
    str.replace("\"", "\\\"");
    str.replace("\n", "\\\n");
    str.replace(QChar(8232), "\\\n"); //ctrl+enter
}


QString HTMLChatView::escapeStringCopy(QString str) {
    str.replace("\"", "\\\"");
    str.replace("\n", "\\\n");
    str.replace(QChar(8232), "\\\n"); //ctrl+enter
    return str;
}


void HTMLChatView::setVisible(bool visible) {
    QWidget::setVisible(visible);
    webView.setVisible(visible);
}


void HTMLChatView::setTheme(const HTMLChatTheme& theme_) {

    qDebug() << "set theme " << theme_.baseHref();

    if (!isReady) {
        delete queuedTheme;
        queuedTheme = new HTMLChatTheme(theme_);
        qDebug() << "queued theme change" << theme_.baseHref();
        return;
    }

    if (theme_ != theme) {
        qDebug() << theme.baseHref() << theme_.baseHref() << theme.currentVariant() << theme_.currentVariant();
        theme = theme_;
        isReady = false;
        webView.setHtml(createEmptyDocument(theme.baseHref(), theme.currentVariant()), theme.baseHref());
    }
    //rest in onEmptyDocumentLoaded
}


bool HTMLChatView::atBottom() const {
    return (webView.page()->mainFrame()->scrollBarMaximum(Qt::Vertical) ==
        webView.page()->mainFrame()->scrollBarValue(Qt::Vertical));
}


void HTMLChatView::scrollToBottom() {
    webView.page()->mainFrame()->setScrollBarValue(
                                                   Qt::Vertical,
                                                   webView.page()->mainFrame()->scrollBarMaximum(Qt::Vertical)
                                                   );
}


void HTMLChatView::scrollToTop() {
    webView.page()->mainFrame()->setScrollBarValue(Qt::Vertical, 0);
}


void HTMLChatView::scrollUp() {
    QWebFrame * frame = webView.page()->mainFrame();
    frame->setScrollBarValue(Qt::Vertical, frame->scrollBarValue(Qt::Vertical) - 150);
}


void HTMLChatView::scrollDown() {
    QWebFrame * frame = webView.page()->mainFrame();
    frame->setScrollBarValue(Qt::Vertical, frame->scrollBarValue(Qt::Vertical) + 150);
}


QSize HTMLChatView::sizeHint() const {
    return minimumSizeHint();
}


bool HTMLChatView::internalFind(const QString& str, bool startFromBeginning) {

    bool found = webView.page()->findText(str, startFromBeginning ?
                                          QWebPage::FindWrapsAroundDocument : (QWebPage::FindFlag)0);

    if (!found && !startFromBeginning) {
        return internalFind(str, true);
    }

    return found;

}


bool HTMLChatView::hasSelectedText() const {
    return !(webView.page()->selectedText().isEmpty());
}


void HTMLChatView::copySelectedText() {
    webView.page()->triggerAction(QWebPage::Copy);
}


void HTMLChatView::contextMenuEvent(QContextMenuEvent* event) {

    QList<QAction*> actions;

    QAction* copyAction = webView.page()->action(QWebPage::Copy);
    actions.append(copyAction);

    QAction* chosen = QMenu::exec(actions, event->globalPos());
    if (chosen == copyAction) {
        webView.page()->triggerAction(QWebPage::Copy);
    }
}


void HTMLChatView::removeTrackBar() {
    if (isReady) { //if webkit is intializing now it couldn't add trackBar (so there'll be no 2 trackbars)
       evaluateJS("psi_removeTrackBar()");
    }
}


void HTMLChatView::addTrackBar() {
    if (isReady) {
        evaluateJS("psi_addTrackBar()");
    }
}