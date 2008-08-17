#ifndef _ESYSTEMCHATEVENT_H
#define	_ESYSTEMCHATEVENT_H

#include "systemchatevent.h"


/** 
 * SystemChatEvent with a text content (description).
 */
class ExtendedSystemChatEvent : public SystemChatEvent {

public:
    /** 
     * Constructor that sets event text to message; 
     *
     * timestamp = current date 
     * type = Other
     */
    ExtendedSystemChatEvent(QString message);

    /** 
     * Constructor that sets event text to message; 
     *
     * timestamp = current date 
     * event type = \param type
     */
    ExtendedSystemChatEvent(QString message, SystemEventType type);

    /** 
     * Constructor.
     *
     * message - unset
     * timestamp = current date 
     * type = Other
     */
    ExtendedSystemChatEvent();

    /** Returns message */
    QString message() const;

    /** Sets message */
    void setMessage(QString message);

protected:
    /** Event description */
    QString message_;

};


#endif

