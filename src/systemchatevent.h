#ifndef _SYSTEMCHATEVENT_H
#define	_SYSTEMCHATEVENT_H

#include <QString>

#include "chatevent.h"
#include "chattheme.h"

class ChatTheme;
class AstractChatEvent;


/**
 * System ChatEvent - displays system message. 
 *
 * For example: dsconnected, encryption enabled. 
 *
 * NOTE: For Error, Other and EndedConversation types you must use 
 * NOTE: ExtendedSystemChatEvent and provide nick/error description.
 *
 */
class SystemChatEvent : public ChatEvent {

public:


    enum SystemEventType {

        EncryptionEnabled,
        EncryptionDisabled,
        Disconnected,
        Reconnecting,
        Connected,
        EndedConvesation,
        AlreadyJoined, //or joining
        Error,
        Other
    };

    /** Constructor that sets event type, timesamp = current date */
    SystemChatEvent(SystemChatEvent::SystemEventType type);

    /** Sets type to other; timestamp = current date */
    SystemChatEvent();

    /** Returns event type */
    SystemChatEvent::SystemEventType type() const;

    /** Sets event type */
    void setType(SystemChatEvent::SystemEventType type);

    /** Text of event */
    virtual QString message() const;

    //reimplemented
    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

protected:
    SystemEventType type_;
};



#endif
