#ifndef _ESYSTEMCHATEVENT_H
#define	_ESYSTEMCHATEVENT_H

#include "systemchatevent.h"


/** SystemChatEvent with text content */
class ExtendedSystemChatEvent : public SystemChatEvent {

public:
    /** Constructor that sets event text to message; timestamp = current date */
    ExtendedSystemChatEvent(QString message);
    ExtendedSystemChatEvent()
        : SystemChatEvent() {};//TODO cto

    /** Reimplemented */
    QString message() const;

    /** Sets message */
    void setMessage(QString message);

protected:
    QString _message;

};


#endif

