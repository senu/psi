#ifndef HAVE_MESSAGE_CHAT_EVENT
#define HAVE_MESSAGE_CHAT_EVENT

#include <Qt>
#include <QString>
#include <QDateTime>

#include "abstractChatEvent.h"

class AbstractChatEvent;

/** Message ChatEvent - incoming/outgoing consecutive/next */
class MessageChatEvent : public AbstractChatEvent
{
public:	

	MessageChatEvent() {}; // I think there's no need for specialized constructors. 
					  // We will have sth like ChatMessage toChatMessage(const XMPP::Message& )

	//getters

	QString jid() const ;
	QString nick() const;
	
	QString subject() const;
	QString body() const;

	QDateTime timestamp() const;
	QString service() const;
	
	QString userIconPath() const;

	
	bool wasEncrypted();

	bool isLocal() const; //our messgage? (outgoing)
	bool isSpooled() const; // offline storage

	bool isConsecutive() const;

	//setters
	
	void setJid(QString);
	void setNick(QString);
	
	void setSubject(QString);
	void setBody(QString);

	void setService(QString);
	void setUserIconPath(QString);

	void setTimestamp(QDateTime);
	bool setWasEncrypted();

	/** Is it our message? */
	void setLocal(bool);		 //our message? (outgoing)
	void setSpooled(bool); 		// offline storage
	void setConsecutive(bool);
	

    //reimplemented 
    QString getRightTemplateAndFillItWithData(const ChatTheme&) const;

  private:
	QString _body;
	QString _nick;
	QString _jid;
	QString _service;
	QString _userIconPath;
	QDateTime _timestamp;

	bool _isConsecutive;
	bool _isSpooled;
	bool _isLocal;

    
}; 

#endif
