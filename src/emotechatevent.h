#ifndef _EMOTECHATEVENT_H
#define	_EMOTECHATEVENT_H

#include <Qt>
#include <QString>

#include "chattheme.h"
#include "userchatdata.h"

class ChatTheme;
class AstractChatEvent;


/** Emote (/me is reading...) ChatEvent */
class EmoteChatEvent : public ChatEvent, public UserChatData {

public:
    /** eg 'is reading' */
    QString message() const;
    void setMessage(QString message);

    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

private:
    QString _message;
    QString _nick;
    bool isLocal_;
};


#endif

