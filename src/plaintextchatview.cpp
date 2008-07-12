#include "plaintextchatview.h"


void __PlainTextChatView::appendEvent(const ChatEvent* event) {
    QString part = event->getRightTemplateAndFillItWithData(theme);
    //TODO ask kev - will we hide PT chat view or destroy it and refill with messages when recreated?
    /*
        if (!alreadyAppended) {
            appendedEvents.append(event);
        }
     **/


    appendText(part);
}


void __PlainTextChatView::appendMessage(const MessageChatEvent* event) {
    QString part;

    if (event->isLocal())
        part = theme.createOutgoingMessagePart(event);
    else
        part = theme.createIncomingMessagePart(event);

    appendText(part);
}


void __PlainTextChatView::clear() {
}


void __PlainTextChatView::init() {
}


void __PlainTextChatView::scrollToBottom() {
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}


void __PlainTextChatView::scrollToTop() {
    verticalScrollBar()->setValue(verticalScrollBar()->minimum());
}


bool __PlainTextChatView::atBottom() const {
    // '32' is 32 pixels margin, which was used in the old code
    return (verticalScrollBar()->maximum() - verticalScrollBar()->value()) <= 32;
    //TODO reimplement in html cv?
}

QScrollBar * __PlainTextChatView::verticalScrollBar() const {
    return textview.verticalScrollBar();
}