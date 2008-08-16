#include "abstractchatevent.h"


AbstractChatEvent::AbstractChatEvent() : timeStamp_(QDateTime::currentDateTime()) {
    qDebug() << "@@@@ MEM WEBKIT: ++++" << "AbstractChatEvent::AbstractChatEvent()" << (int)this; //TODO 112
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
