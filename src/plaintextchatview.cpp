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
}


void __PlainTextChatView::clear() {
}


void __PlainTextChatView::init() {
}
