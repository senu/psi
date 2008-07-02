#include "emotechatevent.h"


QString EmoteChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createEmoteEventPart(this);
}


void EmoteChatEvent::setNick(QString nick) {
    _nick = nick;
}


QString EmoteChatEvent::nick() const {
    return _nick;
}


void EmoteChatEvent::setMessage(QString message) {
    _message = message;
}


QString EmoteChatEvent::message() const {
    return _message;
}


bool EmoteChatEvent::isLocal() const {
    return _isLocal;
}


void EmoteChatEvent::setLocal(bool isLocal) {
    _isLocal = isLocal;
}