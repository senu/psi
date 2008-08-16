#include "chatview.h"
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
    _chatInfo = chatInfo;
}


ChatTheme::ChatInfo ChatView::chatInfo() const {
    return _chatInfo;
}


void ChatView::deleteChatEvents() {
    AbstractChatEvent * event;


    foreach(event, appendedEvents) {
        qDebug() << "%%%%%" << "CV: delete" << (int)event;
        delete event;
    }

    qDebug() << "%%%%%" << "CV: clear()";
    appendedEvents.clear();
}


void ChatView::clear() {
    deleteChatEvents();
}
