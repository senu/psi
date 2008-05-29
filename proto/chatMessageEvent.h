#include <Qt>

class MessageChatEvent : public ChatEvent
{
public:	

	MessageChatEvent() {}; // I think there's no need for specialized constructors. 
					  // We will have sth like ChatMessage toChatMessage(const XMPP::Message& )

	//getters

	QString jid();
	QString nick();
	
	QString subject();
	QString body();

	QDateTime timestamp();
	bool wasEncrypted();

	bool local(); //our messgage? (outgoing)
	bool spooled(); // offline storage

	//setters
	
	QString setJid();
	QString setNick();
	
	QString setSubject();
	QString setBody();

	QDateTime setTimestamp();
	bool setWasEncrypted();

	bool setLocal(); //our messgage? (outgoing)
	bool setSpooled(); // offline storage

	//implemented
	virtual QString getRightTemplateAndFillItWithData(ChatTheme& theme) {			/// ----------------------- 3
		return theme.createOutgoingMessagePart(this);
	}
}; 
