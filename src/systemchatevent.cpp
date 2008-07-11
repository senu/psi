#include <QObject>
#include "systemchatevent.h"


SystemChatEvent::SystemEventType SystemChatEvent::type() const {
    return _type;
}


void SystemChatEvent::setType(SystemChatEvent::SystemEventType type) {
    _type = type;
}


SystemChatEvent::SystemChatEvent(SystemChatEvent::SystemEventType type)
: _type(type) {
    _timeStamp = QDateTime::currentDateTime();
}


SystemChatEvent::SystemChatEvent()
: _type(SystemChatEvent::Other) {

    _timeStamp = QDateTime::currentDateTime();
}


QString SystemChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createSystemEventPart(this);
}


QString SystemChatEvent::message() const {
    QString ret;

    switch (_type) {
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