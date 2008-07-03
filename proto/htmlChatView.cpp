
#include <ios>

#include "htmlChatView.h"
#include <iostream>
#include <qt4/QtCore/qlist.h> //TODO 

#include "config.h"

class MessageChatEvent;


HTMLChatView::HTMLChatView(QWidget * parent, HTMLChatTheme _theme)
: ChatView(parent), theme(_theme) {
    webView.setParent(parent);

    _chatInfo.chatName = "Kot Behemot";
    _chatInfo.destinationName = "Kot Behemot";
    _chatInfo.sourceName = "Pawel Wiejacha";
    _chatInfo.incomingIconPath = "http://a.wordpress.com/avatar/liberumveto-48.jpg";
    _chatInfo.outgoingIconPath = "http://userserve-ak.last.fm/serve/50/4272669.jpg";
    _chatInfo.timeOpened = QDateTime::currentDateTime();

}


void HTMLChatView::clear() {
    //clears Chat div
    appendedEvents.clear();
    evaluateJS("psi_clearMessages()"); //TODO ask Kev - I can reload theme here
}


void HTMLChatView::init() {

    QObject::connect(&webView, SIGNAL(loadFinished(bool)), this, SLOT(onEmptyDocumentLoaded(bool)));
    QObject::connect(webView.page(), SIGNAL(geometryChangeRequested(QRect)), this, SLOT(onDupa(QRect)));
    QObject::connect(&jsNotifier, SIGNAL(onInitFinished()), this, SLOT(onInitDocumentFinished()));
    QObject::connect(&jsNotifier, SIGNAL(onAppendFinished()), this, SLOT(onAppendFinished()));

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
        qDebug() << event;
        if (event->isMessageChatEvent()) {
            appendMessage(dynamic_cast<const MessageChatEvent*> (event), true);
        }
        else {
            appendEvent(dynamic_cast<const ChatEvent*> (event), true);
        }
    }
}


void HTMLChatView::onAppendFinished() {
    qDebug() << "append finished"; //TODO we get this after DOM changed, but before view changed :/
    webView.page()->mainFrame()->setScrollBarValue(Qt::Vertical, 10000); //TODO 
}


void HTMLChatView::onDupa(QRect geom) {
    qDebug() << "dupa" << geom;
    throw 1;
}


QString HTMLChatView::createEmptyDocument(QString baseHref, QString themeVariant) {
    QFile docFile(_THEMEPATH"emptyDocument.html");

    return QString(
                   "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
                   "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">"
                   "<html xmlns=\"http://www.w3.org/1999/xhtml\">"
                   "        <head>"
                   "                <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />"
                   "                <base href=\"%1\"/>"
                   "                <!--"
                   "                <base/>"
                   ""
                   "                TODO3 -->"
                   "                <style id=\"KopeteStyle\" type=\"text/css\" media=\"screen,print\">"
                   "                </style>"
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
    //    qDebug() << "HTMLChatView::evaluateJS(" << scriptSource << ")\n";
}


void HTMLChatView::importJSChatFunctions() {
    // reading from file only while developing	
    QFile file(_THEMEPATH"htmlChatView.js");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

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




