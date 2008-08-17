#ifndef _EMOTECHATEVENT_H
#define	_EMOTECHATEVENT_H

#include <QString>

#include "chattheme.h"
#include "userchatdata.h"

class ChatTheme;
class AstractChatEvent;

/** Emote or Action Message (/me is reading...) ChatEvent */
class EmoteChatEvent : public ChatEvent, public UserChatData {

public:

    /** Emote message, for example 'is reading' */
    QString message() const;
    void setMessage(QString message);

    //reimplemented
    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

private:
    QString message_;
};


#endif
