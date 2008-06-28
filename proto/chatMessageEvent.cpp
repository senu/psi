#include "chatMessageEvent.h"
#include <QtDebug>

QString MessageChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return "NOT IMPLEMENTED !!!!cos(0)";
}

void MessageChatEvent::setBody(QString body) {
    _body = body;
}

QString MessageChatEvent::body() const {
    return _body;
}

void MessageChatEvent::setTimestamp(QDateTime timestamp) {
    _timestamp = timestamp;
}

QDateTime MessageChatEvent::timestamp() const {
    return _timestamp;
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
