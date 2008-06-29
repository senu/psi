#ifndef HAVE_ABSTRACT_CHAT_EVENT
#define HAVE_ABSTRACT_CHAT_EVENT

#include <Qt>
#include <QString>

#include "chatTheme.h"

class ChatTheme;

/** Abstract Chat Event: Messages and FileTransfer/Mood/etc events */
class AbstractChatEvent //TODO name 											
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
