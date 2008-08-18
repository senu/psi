#include "messagechatevent.h"
#include <QtDebug>


MessageChatEvent::MessageChatEvent() {

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


bool MessageChatEvent::isMessageChatEvent() const {
    return true;
}


bool MessageChatEvent::isEmote() const {
    return false;
}