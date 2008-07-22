#include "tunechatevent.h"


TuneChatEvent::TuneChatEvent(const QString& artist, const QString& title)
: UserChatData(), artist_(artist), title_(title) {
}


QString TuneChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createTuneEventPart(this);
}


QString TuneChatEvent::title() const {
    return title_;
}


void TuneChatEvent::setTitle(const QString& title) {
    title_ = title;
}


QString TuneChatEvent::artist() const {
    return artist_;
}


void TuneChatEvent::setArtist(const QString& artist) {
    artist_ = artist;
}


