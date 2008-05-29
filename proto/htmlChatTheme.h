#ifndef HAVE_HTML_CHAT_THEME
#define HAVE_HTML_CHAT_THEME

#include <Qt>

#include "chatTheme.h"
#include "fileTransferChatEvent.h"

class ChatTheme;
class FileTransferChatEvent;
class MessageChatEvent;
class ChatEvent;

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

#endif
