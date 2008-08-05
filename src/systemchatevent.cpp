#include <QObject>
#include "systemchatevent.h"


SystemChatEvent::SystemEventType SystemChatEvent::type() const {
    return type_;
}


void SystemChatEvent::setType(SystemChatEvent::SystemEventType type) {
    type_ = type;
}


SystemChatEvent::SystemChatEvent(SystemChatEvent::SystemEventType type)
: type_(type) {
}


SystemChatEvent::SystemChatEvent()
: type_(SystemChatEvent::Other) {

}


QString SystemChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createSystemEventPart(this);
}


QString SystemChatEvent::message() const {
    QString ret;

    switch (type_) {
        case SystemChatEvent::EncryptionEnabled :
            return "<icon name=\"psi/cryptoYes\"> " + QObject::tr("Encryption Enabled");
        case SystemChatEvent::EncryptionDisabled :
            return "<icon name=\"psi/cryptoNo\"> " + QObject::tr("Encryption Disabled");
        case SystemChatEvent::Disconnected :
                ret = "Disconnected";
            break;
        case SystemChatEvent::Reconnecting :
                ret = "Reconnecting...";
            break;
        case SystemChatEvent::Connected :
                ret = "Reconnecting...";
            break;
        case SystemChatEvent::EndedConvesation :
                //assert(0) //TODO 
        case SystemChatEvent::AlreadyJoined :
                ret = "Error: You are in or joining this room already!";
            break;
        case SystemChatEvent::Error :
            break;
            //assert(0)
        case SystemChatEvent::Other :
            break;
            //assert(0)
    }

    return QObject::tr(ret);
}