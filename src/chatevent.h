#ifndef HAVE_CHAT_EVENT
#define HAVE_CHAT_EVENT

#include <QString>

#include "abstractchatevent.h"


/** 
 * ChatEvent is an AbstractChatEvent that's not MessageChatEvent.
 *
 *  eg. FileTransfer, Status, Mood events
 */
class ChatEvent : public virtual AbstractChatEvent {

public:
    /** 
     * Theme will create QString that represents this chat event.
     * 
     * Better names for this method: createChatEventString,createChatPartFrom or toString.
     * 
     * To avoid reflection, ChatView does not know how to handle ChatEvent, it call
     * ChatEvent::getRightTemplateAndFillItWithData(theme) and appends resulting chat 
     * fragment.
     *
     * This method should call theme.create__EventPart().
     */
    virtual QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const = 0;
};

#endif
