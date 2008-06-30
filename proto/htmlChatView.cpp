#include "htmlChatView.h"
#include <iostream> //TODO 

#include "config.h"

class MessageChatEvent;

HTMLChatView::HTMLChatView(QWidget * parent, HTMLChatTheme _theme)
: ChatView(parent), theme(_theme) {
    webView.setParent(parent);
}


void HTMLChatView::clear() {

}

void HTMLChatView::init() {

    QObject::connect(&webView, SIGNAL(loadFinished(bool)), this, SLOT(onEmptyDocumentLoaded(bool)));
	webView.setHtml(createEmptyDocument(theme.baseHref(), theme.currentVariant()), theme.baseHref());
}


void HTMLChatView::onEmptyDocumentLoaded(bool ok) {
	if(!ok) {
		qDebug() << "ERROR 3";
		exit(1);
	}

	HTMLChatPart header = theme.headerTemplate.createFreshHTMLPart();
	HTMLChatPart footer = theme.footerTemplate.createFreshHTMLPart();

	theme.fillPartWithThemeKeywords(header, "Kot Behemot", QDateTime::currentDateTime());
	theme.fillPartWithThemeKeywords(footer, "Kot Behemot", QDateTime::currentDateTime());

	QString headerStr = header.toString();
	QString footerStr = footer.toString();
			
	escapeString(headerStr);
	escapeString(footerStr);

	importJSChatFunctions();
	evaluateJS("psi_initDocument(\""+ headerStr + "\", \"" + footerStr + "\")");
	
}

QString HTMLChatView::createEmptyDocument(QString baseHref, QString themeVariant) {
	QFile docFile(_THEMEPATH"emptyDocument.html");

	return QString(
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">"
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
"        <body>"
"        </body>"
"</html>").arg(baseHref).arg("Variants/"+QString(themeVariant)+".css");
	
}

void HTMLChatView::appendMessage(const MessageChatEvent* msg) {
    QString part;
	
	if (msg->isLocal())
		part = theme.createOutgoingMessagePart(msg);
	else
		part = theme.createIncomingMessagePart(msg);

    escapeString(part);

//	if(part != QString("<div class=\\\"in content\\\">IIIIIIIIIIIIIII SSS</div>"))
//		throw 43;
//	qDebug() << 'a' << part << '\n' << 'b' << QString("<div class=\\\"in content\\\">IIIIIIIIIIIIIII SSS</div>");

    if (msg->isConsecutive())
        evaluateJS("psi_appendConsecutiveMessage(\"" + part + "\")");
    else
        evaluateJS("psi_appendNextMessage(\"" + part + "\")");

    //TODO
    // Webkit (javascript) must notify us when appending message is completed (we need to scroll after appending not before)      
    webView.page()->mainFrame()->setScrollBarValue(Qt::Vertical, 10000); //TODO 1
}


void HTMLChatView::appendEvent(const ChatEvent* msg) {
    QString part = msg->getRightTemplateAndFillItWithData(theme);
    escapeString(part);

    evaluateJS("psi_appendEvent(\"" + part + "\")");
}


void HTMLChatView::evaluateJS(QString scriptSource) {
    webView.page()->mainFrame()->evaluateJavaScript(scriptSource);
 //   qDebug() << "HTMLChatView::evaluateJS(" << scriptSource << ")\n";
//	std::cout << "cc " << scriptSource.toLatin1().data() << '\n' << std::endl;
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
    QString str = webView.page()->mainFrame()->toHtml();
    printf("%s", str.toLatin1().data());
}


void HTMLChatView::escapeString(QString& str) {
    str.replace("\"", "\\\"");
    str.replace("\n", "\\\n");
}

void HTMLChatView::setVisible(bool visible) {
	QWidget::setVisible(visible);
	webView.setVisible(visible);
}
