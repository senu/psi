#include "esystemchatevent.h"


ExtendedSystemChatEvent::ExtendedSystemChatEvent(QString message)
: SystemChatEvent(), _message(message) {

}


QString ExtendedSystemChatEvent::message() const {
    return _message;
}


void ExtendedSystemChatEvent::setMessage(QString message) {
    _message = message;
}
