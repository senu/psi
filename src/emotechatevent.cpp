#include "emotechatevent.h"


QString EmoteChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createEmoteEventPart(this);
}


void EmoteChatEvent::setMessage(QString message) {
    _message = message;
}


QString EmoteChatEvent::message() const {
    return _message;
}
