#include "moodchatevent.h"

QString MoodChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createMoodEventPart(this);
}


QString MoodChatEvent::text() const {
    return text_;
}


void MoodChatEvent::setText(const QString& text) {
    text_ = text;
}


QString MoodChatEvent::type() const {
    return type_;
}


void MoodChatEvent::setType(const QString& type) {
    type_ = type;
}


