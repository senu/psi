#include "htmlChatTheme.h"

HTMLChatTheme::HTMLChatTheme() 
	: incomingConsecutiveMessageTemplate(
		"<div class=\"nextmessageline\"></div>"
		"<p><span class=\"messagetime consecutive\">%time%</span>senu tu byl</p>"
		"<div id=\"insert\"></div>"),
	 incomingNextMessageTemplate(
			"<div class=\"out content\">"
			"<div class=\"nameheader\"><div class=\"name\"><nobr>%sender%</nobr></div><div class=\"protocol\"><nobr>%service%</nobr></div></div>"
			"<div class=\"spacer\"></div>  <div class=\"buddyicon\"><img src=\"%userIconPath%\" /></div>   <div class=\"messagecontainer\">"              		"<div class=\"messagetop\">   <div class=\"messagetopleft\"></div><div class=\"messagetopright\"></div>    </div>    <div class=\"messagetextcontainer\">                        <div class=\"message\">    <p><span class=\"messagetime\">%time%</span>SENU TU BYL TEZ</p>   <div id=\"insert\"></div>                        </div>   </div></div>  div class=\"spacer\"></div></div>")

{

}


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
	return incomingConsecutiveMessageTemplate.toString();
}


