#ifndef _SYSTEMCHATEVENT_H
#define	_SYSTEMCHATEVENT_H

#include <QString>

#include "chatevent.h"
#include "chattheme.h"

class ChatTheme;
class AstractChatEvent;


/** System ChatEvent (dsconnected/encryption enabled, etc) */
class SystemChatEvent : public ChatEvent {

public:


    enum SystemEventType {

        EncryptionEnabled,
        EncryptionDisabled,
        Disconnected,
        Reconnecting,
        Connected,
        EndedConvesation,
        AlreadyJoined, //or joining!
        Error,
        Other
    };

    /** Constructor that sets event type, timesamp = current date */
    SystemChatEvent(SystemChatEvent::SystemEventType type);
    
    /** type = other; timestamp = current date */
    SystemChatEvent();

    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

    /** Returns event type */
    SystemChatEvent::SystemEventType type() const;

    /** Sets event type */
    void setType(SystemChatEvent::SystemEventType type);

    /** Text of event */
    virtual QString message() const;

protected:
    SystemEventType type_;
};



#endif

