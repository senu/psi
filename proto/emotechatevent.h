#ifndef _EMOTECHATEVENT_H
#define	_EMOTECHATEVENT_H

#include <Qt>
#include <QString>

#include "chatTheme.h"
#include "userchatevent.h"

class ChatTheme;
class AstractChatEvent;


/** Emote (/me is reading...) ChatEvent */
class EmoteChatEvent : public ChatEvent, public UserChatEvent {

public:
    /** eg 'is reading' */
    QString message() const;
    void setMessage(QString message);

    bool isLocal() const;
    void setLocal(bool isLocal);

    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

private:
    QString _message;
    QString _nick;
    bool _isLocal;
};


#endif

