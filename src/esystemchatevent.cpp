#include "esystemchatevent.h"
#include <QObject>


ExtendedSystemChatEvent::ExtendedSystemChatEvent(QString message)
: SystemChatEvent(), message_(message) {

}


ExtendedSystemChatEvent::ExtendedSystemChatEvent(QString message, SystemEventType type)
: SystemChatEvent(), message_(message) {
    type_ = type;
}


QString ExtendedSystemChatEvent::message() const {
    return message_;
}


void ExtendedSystemChatEvent::setMessage(QString message) {
    message_ = message;
}
