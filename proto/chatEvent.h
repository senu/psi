#ifndef HAVE_CHAT_EVENT
#define HAVE_CHAT_EVENT

#include <Qt>

#include "chatTheme.h"

class ChatTheme;

/** Abstract. Messages and FileTransfer/Mood/etc. Events */
class ChatEvent  											
{
  public:	

	/** Creates themed string from event. eg
	 *   <div class="sth"> <b>nick</b> :: message body </div> for HTMLChatTheme and MessageChatEvent or
	 *   <font color="red">Connection broken.</font> for PlainChatTheme and SystemChatEvent
	 *
	 *   it will call theme.theRightTemplate.createChatPart( self )	 	 
	 *
	 **/
	virtual QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const = 0;
}; 

#endif
