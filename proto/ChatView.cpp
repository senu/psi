#include <QWidget>
#include <Qt>
#include <QDateTime>

class ChatEvent;
class MessageChatEvent;
class FileTransferChatEvent;



class ChatTheme 															/// ----------------------- 1
{
public:
	// one methond for each kind of ChatEvent
	
	virtual QString createOutgoingMessagePart(const MessageChatEvent* ) = 0;

	/** creates part using precomputed (precompiled) Contents/Resources/Incoming/FileTransfer.html template in HTMLChatTheme
	 	or handcoded (+ options) string creation in PlainChatTheme */
	virtual QString createFileTransferEventPart(const FileTransferChatEvent* ) = 0; 
	virtual QString createIncomingMessagePart(const MessageChatEvent* ) = 0; 

	//reading theme, precomputing, misc	
};


/** Abstract. Messages and FileTransfer/Mood/etc. Events */
class ChatEvent  															/// ----------------------- 2

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


class FileTransferChatEvent : public ChatEvent 
{
public:	
	enum FileTransferEventType {
		Initiated,
		Aborted,
		Finished,
	};

	FileTransferEventType type;
	QString fileName; //need accessors

	virtual QString getRightTemplateAndFillItWithData(ChatTheme& theme) {			/// ----------------------- 4

		return theme.createFileTransferEventPart(this);
	}
};

class ChatView : public QWidget 
{
Q_OBJECT

public:	
	ChatView(QWidget* Parent); 

	virtual void appendEvent(const ChatEvent& event) = 0;

	/** clears all messges */
	virtual void clear();
	
	virtual ~ChatView();	
};



class HTMLChatTheme : public ChatTheme 
{	
//...	
public:
	//precomputed templates/html parts reading. 
	void readTheme(QString themeName, QString variationName);
	
	QString createIncomingMessagePart(const MessageChatEvent *) 
	{
		return "";
		//returns eg. "<div class="sth"><b>senu@jabster.pl</b> : <span class="messageBody">body</span></div>"
	}
	
	QString createOutgoingMessagePart(const MessageChatEvent *) { 								/// ----------------------- 5

	}

	QString createFileTransferEventPart(const FileTransferChatEvent * event) 					/// ----------------------- 6

	{		
		FileTransferChatEvent::FileTransferEventType type = event->type;

		QString eventText; 

		/*

		switch (type) {
			case Finished:
				eventText = "Finished downloading "	+ event->fileName + ".";
			  	break;
			case FileTransferEventType::Initiated:
				eventText = "Incoming file transfer" + event->fileName + ".";
			  	break;
			case FileTransferEventType::Aborted:
				eventText = "Aborted downloading "	+ event->fileName + ".";
			  	break;							
		}
		 

		HTMLChatTemplate * template = getPrecompiledFTTemplate();
		template->replaceAndEscape('eventSubtype', toString(type)); //replaces %eventSubtype% with type name 
		template->replaceAndEscape('text', eventText);

		QString chatPart = template->toString();

		delete template;
		return chatPart;


		*/
	} 

};


class HTMLChatView : public ChatView  // multiple inheritance ( : QWebView) or QWebView as an attribute - don't know yet. 
{
	public:

//...
	HTMLChatTheme theme; // maybe HTMLChatTheme* to global theme - don't know


	void appendEvent(const ChatEvent& event) 												/// ----------------------- 7

	{
		QString part = event.getRightTemplateAndFillItWithData(theme);

		//findPlaceForNewEventAndInsert(part); 			
		//scrolling, misc. 
	}


};

/** generic HTMLChatTemplate - well QString + few methods*/
class HTMLChatTemplate {

public:

	/** Replaces occurence of %keyword% with escaped value */
	void replaceAndEscapeKeyword(QString keyword, QString value); 

	/** Replaces %keyword% with value */
	void replaceKeyword(QString keyword, QString value); 

	/** Escapes string */
	void escapeString(QString string); 

	/** Converts template to string */
	QString toString();

private:
	/** template body */
	QString contents;

};





int main() {


	return 0;
}



