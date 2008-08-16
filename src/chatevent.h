#ifndef HAVE_CHAT_EVENT
#define HAVE_CHAT_EVENT

#include <Qt>
#include <QString>

#include "abstractchatevent.h"


/** ChatEvent is an AbstractChatEvent that's not MessageChatEvent :D.
 *
 *  eg. FileTransfer, Status, Mood events
 */
class ChatEvent : public virtual AbstractChatEvent {

public:
    virtual QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const = 0;
};

#endif
