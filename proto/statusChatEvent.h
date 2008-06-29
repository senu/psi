#ifndef HAVE_STATUS_CHAT_EVENT
#define HAVE_STATUS_CHAT_EVENT

#include <Qt>
#include <QString>

#include "chatEvent.h"
#include "chatTheme.h"

class ChatTheme;
class AstractChatEvent;

/** Status + status message ChatEvent */
class StatusChatEvent : public ChatEvent 
{
  public:	
	enum StatusEventType {
	    Offline,    
        Away,       
        Xa,         
        Dnd,        
        Chat,       
        Invisible
	};

	StatusEventType type;

	QString statusMessage() const;
	void setStatusMessage(QString);

	QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

  private:
	QString _statusMessage; 
};

#endif
