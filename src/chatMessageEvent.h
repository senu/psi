#ifndef HAVE_MESSAGE_CHAT_EVENT
#define HAVE_MESSAGE_CHAT_EVENT

#include <Qt>
#include <QString>
#include <QDateTime>

#include "abstractChatEvent.h"
#include "userchatevent.h"

class AbstractChatEvent;


/** Message ChatEvent - incoming/outgoing consecutive/next */
class MessageChatEvent : public UserChatEvent {

public:
    MessageChatEvent();

    //getters
    QString subject() const;
    QString body() const;

    bool wasEncrypted();
    bool isConsecutive() const;

    //setters
    void setSubject(QString);
    void setBody(QString);

    bool setWasEncrypted();

    void setConsecutive(bool);

    //reimplemented 
    bool isMessageChatEvent() const;

private:
    QString _body;

    bool _isConsecutive;


};

#endif
