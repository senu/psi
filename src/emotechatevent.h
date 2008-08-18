#ifndef _EMOTECHATEVENT_H
#define	_EMOTECHATEVENT_H

#include <QString>

#include "messagechatevent.h"

/** Emote or Action Message (/me is reading...) ChatEvent */
class EmoteChatEvent : public MessageChatEvent {

public:
    //reimplemented
    bool isConsecutive() const;
    bool isEmote() const;
};


#endif
