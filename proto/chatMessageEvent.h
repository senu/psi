#ifndef HAVE_MESSAGE_CHAT_EVENT
#define HAVE_MESSAGE_CHAT_EVENT

#include <Qt>
#include <QString>
#include <QDateTime>

#include "abstractChatEvent.h"
#include "userchatevent.h"

class AbstractChatEvent;

/** Message ChatEvent - incoming/outgoing consecutive/next */
class MessageChatEvent : public AbstractChatEvent, public UserChatEvent
{
public:	

	MessageChatEvent() {}; // I think there's no need for specialized constructors. 
					  // We will have sth like ChatMessage toChatMessage(const XMPP::Message& )

	//getters
	QString subject() const;
	QString body() const;

	bool wasEncrypted();

	bool isLocal() const; //our messgage? (outgoing)
	bool isSpooled() const; // offline storage

	bool isConsecutive() const;

	//setters
	void setSubject(QString);
	void setBody(QString);

	bool setWasEncrypted();

	/** Is it our message? */
	void setLocal(bool);		 //our message? (outgoing)
	void setSpooled(bool); 		// offline storage
	void setConsecutive(bool);
	

    //reimplemented 
    QString getRightTemplateAndFillItWithData(const ChatTheme&) const;
	bool isMessageChatEvent() const;

  private:
	QString _body;

	bool _isConsecutive;
	bool _isSpooled;
	bool _isLocal;

    
}; 

#endif
