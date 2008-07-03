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

void MessageChatEvent::setNick(QString nick) {
    _nick = nick;
}


QString MessageChatEvent::nick() const {
    return _nick;
}


void MessageChatEvent::setJid(QString jid) {
    _jid = jid;
}


QString MessageChatEvent::jid() const {
    return _jid;
}


QString MessageChatEvent::service() const {
    return _service;
}


void MessageChatEvent::setService(QString service) {
    _service = service;
}


void MessageChatEvent::setUserIconPath(QString userIconPath) {
    _userIconPath = userIconPath;
}


QString MessageChatEvent::userIconPath()const {
    return _userIconPath;
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