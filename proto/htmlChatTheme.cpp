
#include "htmlChatTheme.h"


#include "htmlChatPart.h"

#include <ctime>
#include <QDir>

#include "htmlChatTheme.h"
#include "htmlChatView.h"


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
                          ) {

}


QString HTMLChatTheme::readFileContents(QDir dir, QString relativePath) {
    QFile file(dir.absoluteFilePath(relativePath));
    qDebug() << "loading theme" << dir.absoluteFilePath(relativePath);
    if (!file.open(QIODevice::ReadOnly)) {
        //		throw 'c';			
        qDebug() << "WARNING\n\n" << "file not found"; //TODO 
        return "";
    }

    return file.readAll();
}


void HTMLChatTheme::readTheme(QString path) {
    qDebug() << "opening" << path;
    QDir dir(path + "Contents/");
    qDebug() << dir.entryList();

    setBaseHref(path + "/Contents/Resources/");

    incomingConsecutiveMessageTemplate.setContent(readFileContents(dir, "Resources/Incoming/NextContent.html"));
    incomingNextMessageTemplate.setContent(readFileContents(dir, "Resources/Incoming/Content.html"));

    // outgoing messages
    if (dir.exists("Resources/Outgoing/NextContent.html")) {
        outgoingConsecutiveMessageTemplate.setContent(readFileContents(dir, "Resources/Outgoing/NextContent.html"));
    }
    else {
        outgoingConsecutiveMessageTemplate.setContent(incomingConsecutiveMessageTemplate.content());
    }

    if (dir.exists("Resources/Outgoing/Content.html")) {
        outgoingNextMessageTemplate.setContent(readFileContents(dir, "Resources/Outgoing/Content.html"));
    }
    else {
        outgoingNextMessageTemplate.setContent(incomingNextMessageTemplate.content());
    }


	// status/event template
    fileTransferEventTemplate.setContent(readFileContents(dir, "Resources/Status.html"));


	// action
    if (dir.exists("Resources/Incoming/Action.html")) {
        incomingEmoteEventTemplate.setContent(readFileContents(dir, "Resources/Incoming/Action.html"));
        incomingEmoteEventTemplate.setEmoteTemplate(true);
    }
    else {
        incomingEmoteEventTemplate.setContent(fileTransferEventTemplate.content());
    }

    if (dir.exists("Resources/Outgoing/Action.html")) {
        outgoingEmoteEventTemplate.setContent(readFileContents(dir, "Resources/Outgoing/Action.html"));
        incomingEmoteEventTemplate.setEmoteTemplate(true);
    }
    else {
        outgoingEmoteEventTemplate.setContent(fileTransferEventTemplate.content());
    }


    headerTemplate.setContent(readFileContents(dir, "Resources/Header.html"));
    footerTemplate.setContent(readFileContents(dir, "Resources/Footer.html"));

    //read Variants

    if (!dir.cd("Resources/Variants/")) {
        qDebug() << "no Variants dir";
        return; //no variants
    }

    QStringList filters;
    filters << "*.css";

    QStringList variantFiles = dir.entryList(filters);
    QString variant;

	_variants.clear(); 
	
    foreach(variant, variantFiles) {
        _variants.append(variant.left(variant.size() - 4));
    }

    qDebug() << variants();
}


HTMLChatTheme::HTMLChatTheme(QString path) {
    readTheme(path);
}


QString HTMLChatTheme::createOutgoingMessagePart(const MessageChatEvent * event) const {
    HTMLChatPart part;

    if (event->isConsecutive())
        part = outgoingConsecutiveMessageTemplate.createFreshHTMLPart();
    else {
        part = outgoingNextMessageTemplate.createFreshHTMLPart();
    }

    fillPartWithMessageKeywords(part, event);

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

    StatusChatEvent::StatusEventType type; // = event->type;

    QString eventText = event->statusMessage();

    HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();

    part.replaceAndEscapeKeyword("%message%", eventText);
    part.replaceAndEscapeKeyword("%time%", QDateTime::currentDateTime().toString());
    part.replaceTimeKeyword("time", QDateTime::currentDateTime());

    return part.toString();
}


QString HTMLChatTheme::createEmoteEventPart(const EmoteChatEvent * event) const {

    //QString eventText = QString("%1 %2").arg(event->nick()).arg(event->message());
    QString eventText = event->message(); //TODO no kopete check!
    HTMLChatPart part;

    if (event->isLocal()) {
        part = outgoingEmoteEventTemplate.createFreshHTMLPart();

        if (!outgoingEmoteEventTemplate.isEmoteTemplate()) {
            eventText = event->nick() + " " + eventText;
        }
    }
    else {
        part = incomingEmoteEventTemplate.createFreshHTMLPart();

        if (!incomingEmoteEventTemplate.isEmoteTemplate()) {
            eventText = event->nick() + " " + eventText;
        }
    }

    part.replaceAndEscapeKeyword("%message%", eventText);
    part.replaceAndEscapeKeyword("%sender%", event->nick());
    part.replaceAndEscapeKeyword("%time%", QDateTime::currentDateTime().toString());
    part.replaceTimeKeyword("time", QDateTime::currentDateTime());

    return part.toString();

}


void HTMLChatTheme::fillPartWithMessageKeywords(HTMLChatPart& part, const MessageChatEvent* event) const {

    part.replaceMessageBody(event->body());
    part.replaceAndEscapeKeyword("%time%", event->timestamp().toString());
    part.replaceTimeKeyword("time", QDateTime::currentDateTime());
    part.replaceAndEscapeKeyword("%sender%", event->nick());
    part.replaceAndEscapeKeyword("%service%", event->service());
    part.replaceAndEscapeKeyword("%userIconPath%", event->userIconPath());

}


void HTMLChatTheme::fillPartWithThemeKeywords(HTMLChatPart& part, ChatTheme::ChatInfo sessionInfo) const {

    part.replaceAndEscapeKeyword("%timeOpened%", sessionInfo.timeOpened.toString());
    part.replaceTimeKeyword("timeOpened", sessionInfo.timeOpened);

    part.replaceAndEscapeKeyword("%chatName%", sessionInfo.chatName);

    part.replaceAndEscapeKeyword("%sourceName%", sessionInfo.sourceName);
    part.replaceAndEscapeKeyword("%destinationName%", sessionInfo.destinationName);

    part.replaceAndEscapeKeyword("%incomingIconPath%", sessionInfo.incomingIconPath);
    part.replaceAndEscapeKeyword("%outgoingIconPath%", sessionInfo.outgoingIconPath);
}


QString HTMLChatTheme::createIncomingMessagePart(const MessageChatEvent * event) const {

    HTMLChatPart part;

    if (event->isConsecutive()) {
        part = incomingConsecutiveMessageTemplate.createFreshHTMLPart();
    }
    else {
        part = incomingNextMessageTemplate.createFreshHTMLPart();
    }

    fillPartWithMessageKeywords(part, event);

    return part.toString();
}


QString HTMLChatTheme::baseHref() const {
    return _baseHref;
}


void HTMLChatTheme::setBaseHref(QString baseHref) {
    _baseHref = baseHref;
}


QStringList HTMLChatTheme::variants() const {
    return _variants;
}


QString HTMLChatTheme::currentVariant() const {
    return _currentVariant;
}


void HTMLChatTheme::setCurrentVariant(QString variant) {
    _currentVariant = variant;
}

