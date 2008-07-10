#include "abstractChatEvent.h"


QDateTime AbstractChatEvent::timeStamp() const {
    return _timeStamp;
}


void AbstractChatEvent::setTimeStamp(QDateTime timeStamp) {
    _timeStamp = timeStamp;
}


bool AbstractChatEvent::isMessageChatEvent() const {
    return false;
}
