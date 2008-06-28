#include "htmlChatTheme.h"

HTMLChatTheme::HTMLChatTheme() 
	: incomingConsecutiveMessageTemplate(
		"<div class=\'nextmessageline\'></div>"
		"<p><span class=\'messagetime consecutive\'>%time%</span>%message%</p>"
		"<div id=\'insert\'></div>"),
	 incomingNextMessageTemplate(
			"<div class=\'out content\'>"
			"<div class=\'nameheader\'><div class=\'name\'><nobr>%sender%</nobr></div><div class=\'protocol\'><nobr>%service%</nobr></div></div>"
			"<div class=\'spacer\'></div>  <div class=\'buddyicon\'><img src=\'%userIconPath%\' /></div>   <div class=\'messagecontainer\'>"
            "<div class=\'messagetop\'>   <div class=\'messagetopleft\'></div><div class=\'messagetopright\'></div>    </div>    <div class=\'messagetextcontainer\'>                        <div class=\'message\'>    <p><span class=\'messagetime\'>%time%</span>%message%</p>   <div id=\'insert\'></div>                        </div>   </div></div>  <div class=\'spacer\'></div></div>"), 
	 fileTransferEventTemplate(
		"<div class=\'status content\'>"
        "<div class=\'statusmessage\'><nobr>%message%</nobr></div>"
        "<div class=\'statustime\'>%time%</div>"
		"</div>"
		"<div class=\'spacer\'></div>"		 			 
	)

{

}

//TODO Kev exceptions?
QString HTMLChatTheme::readFileContents(QDir dir, QString relativePath) {
	QFile file(dir.absoluteFilePath(relativePath));
	if(!file.open(QIODevice::ReadOnly)) {
		throw 'c';			
	}

	return file.readAll();
}


HTMLChatTheme::HTMLChatTheme(QString path) {
	qDebug() << "opening" << path;	
	QDir dir(path+"Contents/");
	qDebug() << dir.entryList();

	setBaseHref(path+"/Contents/Resources/");

	
	incomingConsecutiveMessageTemplate.setContent(readFileContents(dir, "Resources/Incoming/NextContent.html"));
	incomingNextMessageTemplate.setContent(readFileContents(dir, "Resources/Incoming/Content.html"));
	
	outgoingConsecutiveMessageTemplate.setContent(readFileContents(dir, "Resources/Outgoing/NextContent.html"));
	outgoingNextMessageTemplate.setContent(readFileContents(dir, "Resources/Outgoing/Content.html"));

	fileTransferEventTemplate.setContent(readFileContents(dir, "Resources/Status.html"));
	
	headerTemplate.setContent(readFileContents(dir, "Resources/Header.html"));
	footerTemplate.setContent(readFileContents(dir, "Resources/Footer.html"));



}  


QString HTMLChatTheme::createOutgoingMessagePart(const MessageChatEvent * event) const {
    HTMLChatPart part;

    if (event->isConsecutive())
        part = outgoingConsecutiveMessageTemplate.createFreshHTMLPart();
    else {
        part = outgoingNextMessageTemplate.createFreshHTMLPart();    
    }

    fillPartWithKeywords(part, event);        

	return part.toString();
}		

QString HTMLChatTheme::createFileTransferEventPart(const FileTransferChatEvent * event) const {		

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
	HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();

    part.replaceAndEscapeKeyword("%message%", "eating breakfast");
    part.replaceAndEscapeKeyword("%time%", QDateTime::currentDateTime().toString());

	return part.toString();
} 

QString HTMLChatTheme::createStatusEventPart(const StatusChatEvent * event) const {		

	StatusChatEvent::StatusEventType type;// = event->type;

	QString eventText = event->statusMessage(); 

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
	HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();

    part.replaceAndEscapeKeyword("%message%", eventText);
    part.replaceAndEscapeKeyword("%time%", QDateTime::currentDateTime().toString());

	return part.toString();
} 

void HTMLChatTheme::fillPartWithKeywords(HTMLChatPart& part, const MessageChatEvent* event) const {

    part.replaceAndEscapeKeyword("%message%", event->body());
    part.replaceAndEscapeKeyword("%time%", event->timestamp().toString());
    part.replaceAndEscapeKeyword("%sender%", event->nick());    
    part.replaceAndEscapeKeyword("%service%", event->service());    

}
QString HTMLChatTheme::createIncomingMessagePart(const MessageChatEvent * event) const  {

    HTMLChatPart part;

    if (event->isConsecutive())
        part = incomingConsecutiveMessageTemplate.createFreshHTMLPart();
    else {
        part = incomingNextMessageTemplate.createFreshHTMLPart();    
    }

    fillPartWithKeywords(part, event);        

	return part.toString();
}


QString HTMLChatTheme::baseHref() const {
	return _baseHref;
}

void HTMLChatTheme::setBaseHref(QString baseHref) {
	_baseHref = baseHref;
} 

