#include <cstring>
#include <ctime>
#include <QDir>

#include "htmlchattheme.h"
#include "htmlchatpart.h"
#include "htmlchatview.h"


HTMLChatTheme::HTMLChatTheme() {
    isValid_ = false;
}


QString HTMLChatTheme::readFileContents(QDir dir, QString relativePath) {
    QFile file(dir.absoluteFilePath(relativePath));
    //    qDebug() << "loading theme file" << dir.absoluteFilePath(relativePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "WARNING\n\n" << "file not found"; //it's not an error. just lazy theme creator 
        return "";
    }

    return file.readAll();
}


void HTMLChatTheme::readTheme(QDir dir) {
    qDebug() << "reading theme from filesystem" << dir;

    isValid_ = false;

    if (!dir.cd("Contents/Resources/")) { //invalid dir
        return; //isValid == false;
    }

    setBaseHref(dir.path() + "/");

    incomingNextMessageTemplate.setContent(readFileContents(dir, "Incoming/Content.html"));

    if (dir.exists("Incoming/NextContent.html")) {
        incomingConsecutiveMessageTemplate.setContent(readFileContents(dir, "Incoming/NextContent.html"));
    }
    else {
        incomingConsecutiveMessageTemplate.setContent(incomingNextMessageTemplate.content());
    }

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

    noOutgoingDir = !dir.exists("Outgoing/buddy_icon.png"); //some themes have empty Outgoing dir
    //we will be using Incoming avatar

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


    headerTemplate_.setContent(readFileContents(dir, "Header.html"));
    footerTemplate_.setContent(readFileContents(dir, "Footer.html"));

    isValid_ = true;

    //read Variants
    variants_.clear();

    if (!dir.cd("Variants/")) {
        qDebug() << "no Variants dir";
        return; //no variants
    }

    QStringList filters;
    filters << "*.css";

    QStringList variantFiles = dir.entryList(filters);
    QString variant;


    foreach(variant, variantFiles) {
        variants_.append(variant.left(variant.size() - 4));
    }

}


HTMLChatTheme::HTMLChatTheme(QString path) {
    readTheme(path);
}


HTMLChatPart HTMLChatTheme::createIncomingMessageHTMLPart(const MessageChatEvent * event) const {

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

    return part;
}

QString HTMLChatTheme::createIncomingMessagePart(const MessageChatEvent * event) const {
    return createIncomingMessageHTMLPart(event).toString();
}


HTMLChatPart HTMLChatTheme::createOutgoingMessageHTMLPart(const MessageChatEvent * event) const {

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

    return part;
}

QString HTMLChatTheme::createOutgoingMessagePart(const MessageChatEvent * event) const {
    return createOutgoingMessageHTMLPart(event).toString();
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
            statusStr = "fileTransferAborted"; //TODO - 48 not in adium!
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
    QString statusType; //adium %status%
    QString statusStr;

    switch (type) {
        case StatusChatEvent::Online :
                statusType = "online";
            statusStr = "Online";
            break;
        case StatusChatEvent::Offline :
                statusType = "offline";
            statusStr = "Offline";
            break;
        case StatusChatEvent::Away :
                statusType = "idle"; //TODO - 49 (adium compatibility) 
            statusStr = "Away";
            break;
        case StatusChatEvent::Xa :
                statusType = "away";
            statusStr = "Not available";
            break;
        case StatusChatEvent::Dnd :
                statusType = "away";
            statusStr = "Do not Disturb";
            break;
        case StatusChatEvent::Chat :
                statusType = "online";
            statusStr = "Free for Chat";
            break;
        case StatusChatEvent::Invisible :
        default:
            statusType = "offline";
            statusStr = "Offline";
            break;
    }

    QString eventText = QObject::tr("%1 is %2").arg(event->nick(), statusStr);

    if (!event->statusMessage().isEmpty()) {
        eventText += " (" + event->statusMessage() + ")";
    }

    HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();

    fillPartWithTimeKeywords(part, event);
    fillPartWithEventKeywords(part, event, eventText);
    part.replaceAndEscapeKeyword("%status%", statusType);
    part.replaceAndEscapeKeyword("%messageClasses%", "status");

    return part.toString();
}


HTMLChatPart HTMLChatTheme::createEmoteEventHTMLPart(const EmoteChatEvent * event) const {

    QString eventText = event->body();
    HTMLChatPart part;

    if (event->isLocal()) {
        part = outgoingEmoteEventTemplate.createFreshHTMLPart();

        if (!outgoingEmoteEventTemplate.isEmoteTemplate()) {
            eventText = event->nick() + " " + eventText;
            part.replaceAndEscapeKeyword("%status%", "emote"); //TODO - 50 ask David Smith
        }
    }
    else {
        part = incomingEmoteEventTemplate.createFreshHTMLPart();

        if (!incomingEmoteEventTemplate.isEmoteTemplate()) {
            eventText = event->nick() + " " + eventText;
            part.replaceAndEscapeKeyword("%status%", "emote"); //TODO - 51 ask David Smith
        }
    }

    fillPartWithTimeKeywords(part, event);
    fillPartWithUserKeywords(part, event);
    part.replaceMessageBody(eventText);
    part.replaceAndEscapeKeyword("%messageClasses%", "event emote");

    return part;
}

QString HTMLChatTheme::createEmoteEventPart(const EmoteChatEvent * event) const {
    return createEmoteEventHTMLPart(event).toString();
}

QString HTMLChatTheme::createSystemEventPart(const SystemChatEvent* event) const {

    HTMLChatPart part = systemEventTemplate.createFreshHTMLPart();

    QString eventText(event->message());

    if (event->type() == SystemChatEvent::EncryptionEnabled) { //append icons
        eventText = "<img name=\"icon://psi/cryptoYes\"> " + eventText;
    }
    else if (event->type() == SystemChatEvent::EncryptionDisabled) {
        eventText = "<img name=\"icon://psi/cryptoNo\"> " + eventText;
    }

    fillPartWithTimeKeywords(part, event);
    fillPartWithEventKeywords(part, event, eventText);
    part.replaceAndEscapeKeyword("%status%", "system");
    part.replaceAndEscapeKeyword("%messageClasses%", "system"); //TODO  - 52 

    return part.toString();
}


QString HTMLChatTheme::createMoodEventPart(const MoodChatEvent* event) const {

    HTMLChatPart part = moodEventTemplate.createFreshHTMLPart();

    QString moodText = QObject::tr("%1 is %2").arg(event->nick(), event->type());

    if (!event->text().isEmpty()) {
        moodText += ": " + event->text();
    }

    fillPartWithTimeKeywords(part, event);
    fillPartWithEventKeywords(part, event, moodText);
    part.replaceAndEscapeKeyword("%status%", "mood");
    part.replaceAndEscapeKeyword("%messageClasses%", "mood"); //TODO - 53

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
    part.replaceAndEscapeKeyword("%messageClasses%", "tune"); //TODO - 54

    return part.toString();
}


void HTMLChatTheme::fillPartWithUserKeywords(HTMLChatPart& part, const UserChatData* event) const {

    part.replaceAndEscapeKeyword("%sender%", event->nick());
    part.replaceAndEscapeKeyword("%service%", event->service());
    part.replaceAndEscapeKeyword("%senderScreenName%", event->jid());
    part.replaceAndEscapeKeyword("%senderDisplayName%", event->jid());

    if (event->userIconPath() == "incoming") { //default incoming avatar 
        part.replaceAndEscapeKeyword("%userIconPath%", defaultIncomingAvatar());
    }
    else if (event->userIconPath() == "outgoing") {
        part.replaceAndEscapeKeyword("%userIconPath%", defaultOutgoingAvatar());
    }
    else { //user avatar
        part.replaceAndEscapeKeyword("%userIconPath%", event->userIconPath());
    }

    part.replaceAndEscapeKeyword("%senderStatusIcon%", event->userStatusIcon());
    part.replaceSenderColorKeyword(event->userColor());

    part.replaceAndEscapeKeyword("%messageDirection%", "ltr");

    //TODO ? 56 %textbackgroundcolor{X}%
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

    //avatars
    if (sessionInfo.incomingIconPath.isEmpty()) {
        part.replaceAndEscapeKeyword("%incomingIconPath%", "incoming_icon.png");
    }
    else {
        part.replaceAndEscapeKeyword("%incomingIconPath%", sessionInfo.incomingIconPath);
    }

    if (sessionInfo.outgoingIconPath.isEmpty()) {
        part.replaceAndEscapeKeyword("%outgoingIconPath%", "outgoing_icon.png");
    }
    else {
        part.replaceAndEscapeKeyword("%outgoingIconPath%", sessionInfo.outgoingIconPath);
    }
}


QString HTMLChatTheme::baseHref() const {
    return baseHref_;
}


void HTMLChatTheme::setBaseHref(QString baseHref) {
    baseHref_ = baseHref;
}


QStringList HTMLChatTheme::variants() const {
    return variants_;
}


QString HTMLChatTheme::currentVariant() const {
    return currentVariant_;
}


void HTMLChatTheme::setCurrentVariant(QString variant) {
    currentVariant_ = variant;
}


bool HTMLChatTheme::isValid() {
    return isValid_;
}


bool HTMLChatTheme::operator==(const HTMLChatTheme& other) const {
    return (other.baseHref() == baseHref() && other.currentVariant() == currentVariant());
}


bool HTMLChatTheme::operator!=(const HTMLChatTheme& other) const {
    return !(*this == other);
}


HTMLChatTemplate HTMLChatTheme::footerTemplate() const {
    return footerTemplate_;
}


HTMLChatTemplate HTMLChatTheme::headerTemplate() const {
    return headerTemplate_;
}


QString HTMLChatTheme::defaultIncomingAvatar() const {
    return "Incoming/buddy_icon.png";
}


QString HTMLChatTheme::defaultOutgoingAvatar() const {
    if (noOutgoingDir) {
        return "Incoming/buddy_icon.png";
    }

    return "Outgoing/buddy_icon.png";
}
