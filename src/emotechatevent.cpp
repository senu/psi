#include "emotechatevent.h"

bool EmoteChatEvent::isConsecutive() const {
    return false;
}

bool EmoteChatEvent::isEmote() const {
    return true;
}