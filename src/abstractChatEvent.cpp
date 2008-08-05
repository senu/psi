#include "abstractChatEvent.h"


AbstractChatEvent::AbstractChatEvent() : timeStamp_(QDateTime::currentDateTime()) {
}


QDateTime AbstractChatEvent::timeStamp() const {
    return timeStamp_;
}


void AbstractChatEvent::setTimeStamp(QDateTime timeStamp) {
    timeStamp_ = timeStamp;
}


bool AbstractChatEvent::isMessageChatEvent() const {
    return false;
}
