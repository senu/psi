#ifndef HAVE_ABSTRACT_CHAT_EVENT
#define HAVE_ABSTRACT_CHAT_EVENT

#include <Qt>
#include <QString>
#include <QDebug> //TODO 112

#include "chattheme.h"

class ChatTheme;


/** 
 * Abstract Chat Event.
 *
 * Base of all Chat Events.
 * 
 * Messages and ChatEvents: FileTransfer, Mood, etc. 
 */
class AbstractChatEvent {

public:
    /** 
     * Default constructor. 
     * 
     * Sets timeStamp to current date. 
     */
    AbstractChatEvent();

    virtual ~AbstractChatEvent();

    /** 
     * Returns true if it's MessageChatEvent 
     *
     * Default implementation returns false.
     */
    virtual bool isMessageChatEvent() const;

    /** Returns timeStamp */
    QDateTime timeStamp() const;

    /** Sets timeStamp */
    void setTimeStamp(QDateTime timeStamp);

protected:

    QDateTime timeStamp_;

};

#endif
