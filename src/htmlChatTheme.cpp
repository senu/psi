
#include <string.h>


#include "htmlChatTheme.h"


#include "htmlChatPart.h"

#include <ctime>
#include <QDir>

#include "htmlChatTheme.h"
#include "htmlChatView.h"


HTMLChatTheme::HTMLChatTheme() {
    _isValid = false;
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


void HTMLChatTheme::readTheme(QDir dir) {
    //    qDebug() << "opening" << path;

    _isValid = false;

    if (!dir.cd("Contents/Resources/")) {
        return; //isValid == false;
    }

    setBaseHref(dir.path() + "/");

    incomingConsecutiveMessageTemplate.setContent(readFileContents(dir, "Incoming/NextContent.html"));
    incomingNextMessageTemplate.setContent(readFileContents(dir, "Incoming/Content.html"));

    // outgoing messages
    if (dir.exists("Outgoing/NextContent.html")) {
        outgoingConsecutiveMessageTemplate.setContent(readFileContents(dir, "Outgoing/NextContent.html"));
    }
    else {
        outgoingConsecutiveMessageTemplate.setContent(incomingConsecutiveMessageTemplate.content());
    }

    if (dir.exists("Outgoing/Content.html")) {
        outgoingNextMessageTemplate.setContent(readFileContents(dir, "Outgoing/Content.html"));
    }
    else {
        outgoingNextMessageTemplate.setContent(incomingNextMessageTemplate.content());
    }


    // status/event template
    fileTransferEventTemplate.setContent(readFileContents(dir, "Status.html"));
    systemEventTemplate = HTMLChatTemplate(fileTransferEventTemplate);
    moodEventTemplate = HTMLChatTemplate(fileTransferEventTemplate);
    tuneEventTemplate = HTMLChatTemplate(fileTransferEventTemplate);


    // action
    if (dir.exists("Incoming/Action.html")) {
        incomingEmoteEventTemplate.setContent(readFileContents(dir, "Incoming/Action.html"));
        incomingEmoteEventTemplate.setEmoteTemplate(true);
    }
    else {
        incomingEmoteEventTemplate.setContent(fileTransferEventTemplate.content());
    }

    if (dir.exists("Outgoing/Action.html")) {
        outgoingEmoteEventTemplate.setContent(readFileContents(dir, "Outgoing/Action.html"));
        incomingEmoteEventTemplate.setEmoteTemplate(true);
    }
    else {
        outgoingEmoteEventTemplate.setContent(fileTransferEventTemplate.content());
    }


    headerTemplate.setContent(readFileContents(dir, "Header.html"));
    footerTemplate.setContent(readFileContents(dir, "Footer.html"));

    _isValid = true;

    //read Variants
    _variants.clear();

    if (!dir.cd("Variants/")) {
        qDebug() << "no Variants dir";
        return; //no variants
    }

    QStringList filters;
    filters << "*.css";

    QStringList variantFiles = dir.entryList(filters);
    QString variant;


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

    fillPartWithTimeKeywords(part, event);
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

    fillPartWithTimeKeywords(part, event);
    fillPartWithUserKeywords(part, event);
    part.replaceMessageBody(event->body());
    part.replaceAndEscapeKeyword("%messageClasses%", "message outgoing");

    return part.toString();
}


QString HTMLChatTheme::createFileTransferEventPart(const FileTransferChatEvent * event) const {

    FileTransferChatEvent::FileTransferEventType type = event->type;

    QString eventText, statusStr; //adium %status%

    switch (type) {
        case FileTransferChatEvent::Finished :

                eventText = QObject::tr("Finished downloading %1.").arg(event->fileName());
            statusStr = "fileTransferComplete";
            break;
        case FileTransferChatEvent::Initiated :
                eventText = QObject::tr("Incoming file transfer: %1.").arg(event->fileName());
            statusStr = "fileTransferBegan";
            break;
        case FileTransferChatEvent::Aborted :
                eventText = QObject::tr("Aborted downloading %1.").arg(event->fileName());
            statusStr = "fileTransferAborted"; //TODO not in adium!
            break;
    }

    HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();

    fillPartWithTimeKeywords(part, event);
    fillPartWithEventKeywords(part, event, eventText);
    part.replaceAndEscapeKeyword("%status%", statusStr);
    part.replaceAndEscapeKeyword("%messageClasses%", "event fileTransfer");

    qDebug() << "theme::FT event" << eventText;
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
        default:
            statusStr = "offline";
            break;
    }

    QString eventText = QObject::tr("%1 is %2").arg(event->nick(), statusStr);

    if (!event->statusMessage().isEmpty()) {
        eventText += " (" + event->statusMessage() + ")";
    }

    HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();

    fillPartWithTimeKeywords(part, event);
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

    fillPartWithTimeKeywords(part, event);
    fillPartWithUserKeywords(part, event);
    part.replaceAndEscapeKeyword("%message%", eventText); 
    part.replaceAndEscapeKeyword("%messageClasses%", "event emote");

    return part.toString();

}


QString HTMLChatTheme::createSystemEventPart(const SystemChatEvent* event) const {

    HTMLChatPart part = systemEventTemplate.createFreshHTMLPart();

    fillPartWithTimeKeywords(part, event);
    fillPartWithEventKeywords(part, event, event->message());
    part.replaceAndEscapeKeyword("%status%", "system");
    part.replaceAndEscapeKeyword("%messageClasses%", "system"); //TODO

    return part.toString();
}


QString HTMLChatTheme::createMoodEventPart(const MoodChatEvent* event) const {

    HTMLChatPart part = moodEventTemplate.createFreshHTMLPart();

    QString moodText(event->type());

    if (!event->text().isEmpty()) {
        moodText += ": " + event->text();
    }

    fillPartWithTimeKeywords(part, event);
    fillPartWithEventKeywords(part, event, moodText);
    part.replaceAndEscapeKeyword("%status%", "mood");
    part.replaceAndEscapeKeyword("%messageClasses%", "mood"); //TODO

    return part.toString();

}


QString HTMLChatTheme::createTuneEventPart(const TuneChatEvent* event) const {

    HTMLChatPart part = tuneEventTemplate.createFreshHTMLPart();

    QString tuneText(event->title());

    if (!event->artist().isEmpty()) {
        tuneText = event->artist() + " - " + tuneText;
    }

    tuneText = QObject::tr("%1 is listeing to %2").arg(event->nick(), tuneText);

    fillPartWithTimeKeywords(part, event);
    fillPartWithUserKeywords(part, event);
    part.replaceAndEscapeKeyword("%message%", tuneText);
    part.replaceAndEscapeKeyword("%status%", "tune");
    part.replaceAndEscapeKeyword("%messageClasses%", "tune"); //TODO

    return part.toString();
}


void HTMLChatTheme::fillPartWithUserKeywords(HTMLChatPart& part, const UserChatData* event) const {

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
    Q_UNUSED(event);
    part.replaceAndEscapeKeyword("%message%", eventText); 
}


void HTMLChatTheme::fillPartWithTimeKeywords(HTMLChatPart& part, const AbstractChatEvent* event) const {
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


bool HTMLChatTheme::isValid() {
    return _isValid;
}


bool HTMLChatTheme::operator==(const HTMLChatTheme& other) const {
    return (other.baseHref() == baseHref() && other.currentVariant() == currentVariant());
}


bool HTMLChatTheme::operator!=(const HTMLChatTheme& other) const {
    return !(*this == other);
}