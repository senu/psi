#include "chatView.h"
#include "messagechatevent.h"

class MessageChatEvent;


void ChatView::restoreDataFrom(const ChatView& other) {
    _chatInfo = other._chatInfo;
    appendedEvents = other.appendedEvents;
}


void ChatView::init(const ChatTheme::ChatInfo& chatInfo) {
    _chatInfo = chatInfo;
    init();
}


void ChatView::appendEvent(const ChatEvent* event, bool alreadyAppended) {
    if (!alreadyAppended) {
        appendedEvents.append(event);
    }
}


void ChatView::appendMessage(const MessageChatEvent* event, bool alreadyAppended) {
    if (!alreadyAppended) {
        appendedEvents.append(event);
    }
}


void ChatView::reappendEvents() {

    const AbstractChatEvent* event;


    foreach(event, appendedEvents) {
        if (event->isMessageChatEvent()) {
            appendMessage(dynamic_cast<const MessageChatEvent*> (event), true);
        }
        else {
            appendEvent(dynamic_cast<const ChatEvent*> (event), true);
        }
    }
}