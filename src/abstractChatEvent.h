#ifndef HAVE_ABSTRACT_CHAT_EVENT
#define HAVE_ABSTRACT_CHAT_EVENT

#include <Qt>
#include <QString>

#include "chatTheme.h"

class ChatTheme;


/** Abstract Chat Event: Messages and FileTransfer/Mood/etc events */
class AbstractChatEvent {

public:
    /** Returns true if it's MessageChatEvent */
    virtual bool isMessageChatEvent() const;

    /** Returns timeStamp */
    QDateTime timeStamp() const;

    /** Sets timeStamp */
    void setTimeStamp(QDateTime timeStamp);

private:

    QDateTime _timeStamp;

};

#endif
