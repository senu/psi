#include <QUrl>
#include <QTimer>
#include <QList>
#include <QWidget>
#include <QMessageBox>

#include "htmlChatView.h"

class MessageChatEvent;


HTMLChatView::HTMLChatView(QWidget * parent, HTMLChatTheme _theme, QString _themePath)
: ChatView(parent), themePath(_themePath), theme(_theme) {
    webView.setParent(parent);

    webView.page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    webView.setContextMenuPolicy(Qt::NoContextMenu);

    _chatInfo.chatName = "Kot Behemot";
    _chatInfo.destinationName = "Kot Behemot";
    _chatInfo.destinationDisplayName = "behemot@jabber.ru";
    _chatInfo.sourceName = "Pawel Wiejacha";
    _chatInfo.incomingIconPath = "http://a.wordpress.com/avatar/liberumveto-48.jpg";
    _chatInfo.outgoingIconPath = "http://userserve-ak.last.fm/serve/50/4272669.jpg";
    _chatInfo.timeOpened = QDateTime::currentDateTime();

    connect(webView.page(), SIGNAL(linkClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));

}


void HTMLChatView::clear() {
    //clears Chat div
    appendedEvents.clear();
    evaluateJS("psi_clearMessages()");
}


void HTMLChatView::init() {

    connect(&webView, SIGNAL(loadFinished(bool)), this, SLOT(onEmptyDocumentLoaded(bool)));
    connect(&jsNotifier, SIGNAL(onInitFinished()), this, SLOT(onInitDocumentFinished()));
    connect(&jsNotifier, SIGNAL(onAppendFinished()), this, SLOT(onAppendFinished()));

    webView.setHtml(createEmptyDocument(theme.baseHref(), theme.currentVariant()), theme.baseHref());
    //rest in onEmptyDocumentLoaded
}


void HTMLChatView::onEmptyDocumentLoaded(bool ok) {
    if (!ok) { //TODO CTRM eg. when we delete this object
        qDebug() << "ERROR 3";
        exit(1); //TODO
    }

    HTMLChatPart header = theme.headerTemplate.createFreshHTMLPart();
    HTMLChatPart footer = theme.footerTemplate.createFreshHTMLPart();


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

    const AbstractChatEvent* event;


    foreach(event, appendedEvents) {
        if (event->isMessageChatEvent()) {
            appendMessage(dynamic_cast<const MessageChatEvent*> (event), true);
        }
        else {
            appendEvent(dynamic_cast<const ChatEvent*> (event), true);
        }
    }

    emit initDocumentFinished();
}


void HTMLChatView::onAppendFinished() {
    QTimer::singleShot(0, this, SLOT(onDoScrolling())); //advice from qt mailing list
}


void HTMLChatView::onDoScrolling() {
    scrollToBottom();
    emit appendFinished();
}


void HTMLChatView::onLinkClicked(const QUrl& url) {
    QMessageBox::about(this, "open url", url.toString());
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
    QString part;

    if (msg->isLocal())
        part = theme.createOutgoingMessagePart(msg);
    else
        part = theme.createIncomingMessagePart(msg);

    escapeString(part);

    if (msg->isConsecutive()) {
        if (!alreadyAppended) {
            appendedEvents.append(msg);
        }
        evaluateJS("psi_appendConsecutiveMessage(\"" + part + "\", \"" +
                   escapeStringCopy(msg->body()) + "\"" + ")");
    }
    else {
        if (!alreadyAppended) {
            appendedEvents.append(msg);
        }
        evaluateJS("psi_appendNextMessage(\"" + part + "\", \"" +
                   escapeStringCopy(msg->body()) + "\"" + ")");
    }
}


void HTMLChatView::appendEvent(const ChatEvent* event, bool alreadyAppended = false) {
    QString part = event->getRightTemplateAndFillItWithData(theme);
    escapeString(part);

    if (!alreadyAppended) {
        appendedEvents.append(event);
    }

    evaluateJS("psi_appendEvent(\"" + part + "\")");
}


void HTMLChatView::appendMessage(const MessageChatEvent* msg) {
    appendMessage(msg, false);
}


void HTMLChatView::appendEvent(const ChatEvent* event) {
    appendEvent(event, false);
}


void HTMLChatView::evaluateJS(QString scriptSource) {
    webView.page()->mainFrame()->evaluateJavaScript(scriptSource);
    //    Debug() << "HTMLChatView::evaluateJS(" << scriptSource << ")\n";
}


void HTMLChatView::importJSChatFunctions() {
    // reading from file only while developing	
    QFile file(themePath + "/htmlChatView.js");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        exit(7);
    }

    QString jsCode = file.readAll();
    evaluateJS(jsCode);

}


HTMLChatView::~HTMLChatView() {
        qDebug() << dumpContent();
}


QString HTMLChatView::dumpContent() {
    return webView.page()->mainFrame()->toHtml();
}


void HTMLChatView::escapeString(QString& str) {
    str.replace("\"", "\\\"");
    str.replace("\n", "\\\n");
}


QString HTMLChatView::escapeStringCopy(QString str) {
    str.replace("\"", "\\\"");
    str.replace("\n", "\\\n");
    return str;
}


void HTMLChatView::setVisible(bool visible) {
    QWidget::setVisible(visible);
    webView.setVisible(visible);
}


void HTMLChatView::setChatInfo(ChatTheme::ChatInfo chatInfo) {
    _chatInfo = chatInfo;
}


ChatTheme::ChatInfo HTMLChatView::chatInfo() const {
    return _chatInfo;
}


void HTMLChatView::setTheme(HTMLChatTheme _theme) {
    theme = _theme;
    webView.setHtml(createEmptyDocument(theme.baseHref(), theme.currentVariant()), theme.baseHref());
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

