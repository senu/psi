#include "htmlChatTheme.h"


QString HTMLChatTheme::createOutgoingMessagePart(const MessageChatEvent *) {
	return "UNIMPLEMENTED";
}		

QString HTMLChatTheme::createFileTransferEventPart(const FileTransferChatEvent * event) {		

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
	return "UNIMPLEMENTED";

} 

QString HTMLChatTheme::createIncomingMessagePart(const MessageChatEvent *)  {
	return "UNIMPLEMENTED";
}


