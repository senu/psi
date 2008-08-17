#include "chatview.h"
#include "messagechatevent.h"


void ChatView::restoreDataFrom(const ChatView& other) {
    chatInfo_ = other.chatInfo_;
    appendedEvents = other.appendedEvents;
}


ChatView::~ChatView() {

}


void ChatView::init(const ChatTheme::ChatInfo& chatInfo) {
    chatInfo_ = chatInfo;
    init();
}


void ChatView::appendEvent(ChatEvent* event, bool alreadyAppended) {
    if (!alreadyAppended) {
        appendedEvents.append(event);
    }
}


void ChatView::appendMessage(MessageChatEvent* event, bool alreadyAppended) {
    if (!alreadyAppended) {
        appendedEvents.append(event);
    }
}


void ChatView::reappendEvents() {

    AbstractChatEvent* event;


    foreach(event, appendedEvents) {
        if (event->isMessageChatEvent()) {
            appendMessage(dynamic_cast<MessageChatEvent*> (event), true);
        }
        else {
            appendEvent(dynamic_cast<ChatEvent*> (event), true);
        }
    }
}


void ChatView::setChatInfo(ChatTheme::ChatInfo chatInfo) {
    chatInfo_ = chatInfo;
}


ChatTheme::ChatInfo ChatView::chatInfo() const {
    return chatInfo_;
}


void ChatView::deleteChatEvents() {
    AbstractChatEvent * event;


    foreach(event, appendedEvents) {
        delete event;
    }

    appendedEvents.clear();
}


void ChatView::clear() {
    deleteChatEvents();
}
