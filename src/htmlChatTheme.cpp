
#include "htmlChatTheme.h"


#include "htmlChatPart.h"

#include <ctime>
#include <QDir>

#include "htmlChatTheme.h"
#include "htmlChatView.h"


HTMLChatTheme::HTMLChatTheme() {
}


QString HTMLChatTheme::readFileContents(QDir dir, QString relativePath) {
    QFile file(dir.absoluteFilePath(relativePath));
    qDebug() << "loading theme file" << dir.absoluteFilePath(relativePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "WARNING\n\n" << "file not found"; //TODO 
        return "";
    }

    return file.readAll();
}


void HTMLChatTheme::readTheme(QString path) {
    //    qDebug() << "opening" << path;
    QDir dir(path + "Contents/");

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
    systemEventTemplate.setContent(readFileContents(dir, "Resources/Status.html"));


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

    //qDebug() << variants();
}


HTMLChatTheme::HTMLChatTheme(QString path) {
    readTheme(path);
}


QString HTMLChatTheme::createIncomingMessagePart(const MessageChatEvent * event) const {

    HTMLChatPart part;

    if (event->isConsecutive()) {
        part = incomingConsecutiveMessageTemplate.createFreshHTMLPart();
    }
    else {
        part = incomingNextMessageTemplate.createFreshHTMLPart();
    }

    fillPartWithUserKeywords(part, event);
    part.replaceMessageBody(event->body());
    part.replaceAndEscapeKeyword("%messageClasses%", "message incoming");

    return part.toString();
}


QString HTMLChatTheme::createOutgoingMessagePart(const MessageChatEvent * event) const {

    HTMLChatPart part;

    if (event->isConsecutive()) {
        part = outgoingConsecutiveMessageTemplate.createFreshHTMLPart();
    }
    else {
        part = outgoingNextMessageTemplate.createFreshHTMLPart();
    }

    fillPartWithUserKeywords(part, event);
    part.replaceMessageBody(event->body());
    part.replaceAndEscapeKeyword("%messageClasses%", "message outgoing");

    return part.toString();
}


QString HTMLChatTheme::createFileTransferEventPart(const FileTransferChatEvent * event) const {

    FileTransferChatEvent::FileTransferEventType type = event->type;

    QString eventText, //TODO translate
        statusStr; //%status%


    switch (type) {
        case FileTransferChatEvent::Finished :

                eventText = "Finished downloading " + event->fileName() + ".";
            statusStr = "fileTransferComplete";
            break;
        case FileTransferChatEvent::Initiated :
                eventText = "Incoming file transfer" + event->fileName() + ".";
            statusStr = "fileTransferBegan";
            break;
        case FileTransferChatEvent::Aborted :
                eventText = "Aborted downloading " + event->fileName() + ".";
            statusStr = "fileTransferAborted"; //TODO not in adium!
            break;
    }

    HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();
    fillPartWithEventKeywords(part, event, eventText);
    part.replaceAndEscapeKeyword("%status%", statusStr);
    part.replaceAndEscapeKeyword("%messageClasses%", "event fileTransfer");

    return part.toString();
}


QString HTMLChatTheme::createStatusEventPart(const StatusChatEvent * event) const {

    StatusChatEvent::StatusEventType type = event->type;
    QString statusStr; //adium %status%

    switch (type) {
        case StatusChatEvent::Online :
                statusStr = "online";
            break;
        case StatusChatEvent::Offline :
                statusStr = "offline";
            break;
        case StatusChatEvent::Away :
                statusStr = "idle"; //TODO ask Kev (adium compatibility)
            break;
        case StatusChatEvent::Xa :
                statusStr = "away";
            break;
        case StatusChatEvent::Dnd :
                statusStr = "away";
            break;
        case StatusChatEvent::Chat :
                statusStr = "online";
            break;
        case StatusChatEvent::Invisible : //TODO - ?!?
                statusStr = "offline";
            break;
    }

    QString eventText = event->statusMessage();

    HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();

    fillPartWithEventKeywords(part, event, eventText);
    part.replaceAndEscapeKeyword("%status%", statusStr);
    part.replaceAndEscapeKeyword("%messageClasses%", "status");

    return part.toString();
}


QString HTMLChatTheme::createEmoteEventPart(const EmoteChatEvent * event) const {

    QString eventText = event->message();
    HTMLChatPart part;

    if (event->isLocal()) {
        part = outgoingEmoteEventTemplate.createFreshHTMLPart();

        if (!outgoingEmoteEventTemplate.isEmoteTemplate()) {
            eventText = event->nick() + " " + eventText;
            part.replaceAndEscapeKeyword("%status%", "emote"); //TODO ask David Smith
        }
    }
    else {
        part = incomingEmoteEventTemplate.createFreshHTMLPart();

        if (!incomingEmoteEventTemplate.isEmoteTemplate()) {
            eventText = event->nick() + " " + eventText;
            part.replaceAndEscapeKeyword("%status%", "emote"); //TODO ask David Smith
        }
    }

    fillPartWithUserKeywords(part, event);
    part.replaceAndEscapeKeyword("%message%", eventText); //TODO validate or escape
    part.replaceAndEscapeKeyword("%messageClasses%", "event emote");

    return part.toString();

}


QString HTMLChatTheme::createSystemEventPart(const SystemChatEvent* event) const {
    HTMLChatPart part = systemEventTemplate.createFreshHTMLPart();

    fillPartWithEventKeywords(part, event, event->message());
    part.replaceAndEscapeKeyword("%status%", "system");
    part.replaceAndEscapeKeyword("%messageClasses%", "system");//TODO
    
    return part.toString();
}


void HTMLChatTheme::fillPartWithUserKeywords(HTMLChatPart& part, const UserChatEvent* event) const {

    part.replaceAndEscapeKeyword("%time%", event->timeStamp().toString());
    part.replaceTimeKeyword("time", event->timeStamp());
    part.replaceAndEscapeKeyword("%shortTime%", HTMLChatPart::createShortTime(event->timeStamp()));

    part.replaceAndEscapeKeyword("%sender%", event->nick());
    part.replaceAndEscapeKeyword("%service%", event->service());
    part.replaceAndEscapeKeyword("%senderScreenName%", event->jid());
    part.replaceAndEscapeKeyword("%senderDisplayName%", event->jid());
    part.replaceAndEscapeKeyword("%userIconPath%", event->userIconPath());
    part.replaceAndEscapeKeyword("%senderStatusIcon%", event->userStatusIcon());
    part.replaceSenderColorKeyword(event->userHash());

    part.replaceAndEscapeKeyword("%messageDirection%", "ltr"); //TODO

    //TODO %textbackgroundcolor{X}%
}


void HTMLChatTheme::fillPartWithEventKeywords(HTMLChatPart& part, const ChatEvent* event, QString eventText) const {
    part.replaceAndEscapeKeyword("%message%", eventText); //TODO validate or escape
    part.replaceAndEscapeKeyword("%time%", event->timeStamp().toString());
    part.replaceTimeKeyword("time", event->timeStamp());
    part.replaceAndEscapeKeyword("%shortTime%", HTMLChatPart::createShortTime(event->timeStamp()));
}


void HTMLChatTheme::fillPartWithThemeKeywords(HTMLChatPart& part, ChatTheme::ChatInfo sessionInfo) const {

    part.replaceAndEscapeKeyword("%timeOpened%", sessionInfo.timeOpened.toString());
    part.replaceTimeKeyword("timeOpened", sessionInfo.timeOpened);

    part.replaceAndEscapeKeyword("%chatName%", sessionInfo.chatName);

    part.replaceAndEscapeKeyword("%sourceName%", sessionInfo.sourceName);
    part.replaceAndEscapeKeyword("%destinationName%", sessionInfo.destinationName);

    part.replaceAndEscapeKeyword("%destinationDisplayName%", sessionInfo.destinationName);

    part.replaceAndEscapeKeyword("%incomingIconPath%", sessionInfo.incomingIconPath);
    part.replaceAndEscapeKeyword("%outgoingIconPath%", sessionInfo.outgoingIconPath);
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

