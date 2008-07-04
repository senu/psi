#include "chatMessageEvent.h"
#include <QtDebug>


QString MessageChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return "NOT IMPLEMENTED !!!!cos(0)"; //TODO move 
}


void MessageChatEvent::setBody(QString body) {
    _body = body;
}


QString MessageChatEvent::body() const {
    return _body;
}


void MessageChatEvent::setConsecutive(bool is) {
    _isConsecutive = is;
}


bool MessageChatEvent::isConsecutive() const {
    return _isConsecutive;
}


void MessageChatEvent::setLocal(bool is) {
    _isLocal = is;
}


bool MessageChatEvent::isLocal() const {
    return _isLocal;
}


bool MessageChatEvent::isMessageChatEvent() const {
    return true;
}