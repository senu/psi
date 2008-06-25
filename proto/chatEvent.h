#ifndef HAVE_CHAT_EVENT
#define HAVE_CHAT_EVENT

#include <Qt>
#include <QString>

#include "abstractChatEvent.h"

/** ChatEvent is an AbstractChatEvent that's not MessageChatEvent :D.
 *
 *  eg. FileTransfer, Status, Mood events
 */
class ChatEvent : public AbstractChatEvent {
  public:	
	QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const = 0;

};

#endif
