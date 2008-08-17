#include <QObject>
#include "systemchatevent.h"


SystemChatEvent::SystemChatEvent(SystemChatEvent::SystemEventType type) : type_(type) {
}


SystemChatEvent::SystemChatEvent() : type_(SystemChatEvent::Other) {

}


SystemChatEvent::SystemEventType SystemChatEvent::type() const {
    return type_;
}


void SystemChatEvent::setType(SystemChatEvent::SystemEventType type) {
    type_ = type;
}


QString SystemChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createSystemEventPart(this);
}


QString SystemChatEvent::message() const {
    QString ret;

    switch (type_) {
        case SystemChatEvent::EncryptionEnabled :
                ret = "Encryption Enabled";
            break;
        case SystemChatEvent::EncryptionDisabled :
                ret = "Encryption Disabled";
            break;
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
                Q_ASSERT(0);
        case SystemChatEvent::AlreadyJoined :
                ret = "Error: You are in or joining this room already!";
            break;
        case SystemChatEvent::Error :
                Q_ASSERT(0);
            break;
        case SystemChatEvent::Other :
                Q_ASSERT(0);
            break;
    }

    return QObject::tr(ret);
}
