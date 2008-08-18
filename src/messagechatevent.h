#ifndef HAVE_MESSAGE_CHAT_EVENT
#define HAVE_MESSAGE_CHAT_EVENT

#include <Qt>
#include <QString>
#include <QDateTime>

#include "abstractchatevent.h"
#include "userchatdata.h"

class AbstractChatEvent;


/** 
 * Message ChatEvent 
 * 
 * Can be incoming or outgoing and consecutive or next.
 * It's base class of EmoteChatEvent.
 */
class MessageChatEvent : public AbstractChatEvent, public UserChatData {

public:
    MessageChatEvent();

    //getters
    QString subject() const;
    QString body() const;

    bool wasEncrypted();
    virtual bool isConsecutive() const;

    /** 
     * Returns true if it's Action/Emote message.
     *
     * Default implementation returns false; 
     */
    virtual bool isEmote() const;

    //setters
    void setSubject(QString);
    void setBody(QString);
    
    /** Currently unused */
    void setWasEncrypted();
    void setConsecutive(bool);

    //reimplemented 
    bool isMessageChatEvent() const;

private:
    
    /** Messag body*/
    QString _body;

    /** Message successiveness */
    bool _isConsecutive;
};

#endif
