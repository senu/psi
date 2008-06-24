#include "htmlChatView.h"

class MessageChatEvent;

void HTMLChatView::clear() {

}

void HTMLChatView::appendEvent(const ChatEvent& event) {
	QString part = event.getRightTemplateAndFillItWithData(theme);

	//findPlaceForNewEventAndInsert(part); 			
	//scrolling, misc. 
}

void HTMLChatView::appendMessage(const MessageChatEvent* msg) {
    if (msg->isConsecutive())
	    evaluateJS("psi_appendConsecutiveMessage(\"" + theme.createIncomingMessagePart(msg) + "\")");
    else
    	evaluateJS("psi_appendNextMessage(\"" + theme.createIncomingMessagePart(msg) + "\")");

    //TODO
    // Webkit (javascript) must notify us when appending message is completed (we need to scroll after appending not before)      
    webView.page()->mainFrame()->setScrollBarValue(Qt::Vertical, 10000); //TODO 1

}

void HTMLChatView::evaluateJS(QString scriptSource) {
    webView.page()->mainFrame()->evaluateJavaScript(scriptSource);
   // qDebug() << "HTMLChatView::evaluateJS(" << scriptSource <<  ")\n";
}
void HTMLChatView::importJSChatFunctions() {
    // reading from file only while developing	
    QFile file("htmlChatView.js");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

    QString jsCode = file.readAll();

    evaluateJS(jsCode);

}

HTMLChatView::~HTMLChatView() {
	QString str = webView.page()->mainFrame()->toHtml();
	printf("%s", str.toLatin1().data());
}

