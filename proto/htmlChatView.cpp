#include "htmlChatView.h"

void HTMLChatView::clear() {

}

void HTMLChatView::appendEvent(const ChatEvent& event) {
	QString part = event.getRightTemplateAndFillItWithData(theme);

	//findPlaceForNewEventAndInsert(part); 			
	//scrolling, misc. 
}

void HTMLChatView::appendNextMessage() {
	evaluateJS("psi_appendNextMessage()");
}

void HTMLChatView::appendConsecutiveMessage() {
	evaluateJS("psi_appendConsecutiveMessage()");
}

