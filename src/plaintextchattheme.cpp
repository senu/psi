#include "plaintextchattheme.h"


PlainTextChatTheme::PlainTextChatTheme() {

}


QString PlainTextChatTheme::createEmoteEventPart(const EmoteChatEvent * event) const {

    QString color = colorString(event->isLocal(), event->isSpooled());

    return QString("<span style=\"color: %1\">").arg(color)
        + QString("[%1]").arg(formatTimeStamp(event->timeStamp()))
        + QString(" *%1 ").arg(event->nick())
        + event->body() + "</span>";
}


QString PlainTextChatTheme::createIncomingMessagePart(const MessageChatEvent * event) const {

    QString color(colorString(event->isLocal(), event->isSpooled()));
    QString timeStr(formatTimeStamp(event->timeStamp()));

    if (useChatSaysStyle()) {
        return QString("<p style=\"color: %1\">").arg(color) + QString("[%1] ").arg(timeStr)
            + QObject::tr("%1 says:").arg(event->nick()) + "</p>" + event->body();
    }
    else {
        return QString("<span style=\"color: %1\">").arg(color) + QString("[%1] &lt;").arg(timeStr)
            + event->nick() + QString("&gt;</span> ") + event->body();
    }
}


QString PlainTextChatTheme::createOutgoingMessagePart(const MessageChatEvent * event) const {
    return createIncomingMessagePart(event);
}


QString PlainTextChatTheme::createFileTransferEventPart(const FileTransferChatEvent * event) const {

    FileTransferChatEvent::FileTransferEventType type = event->type;

    QString eventText;

    switch (type) {
        case FileTransferChatEvent::Finished :
                eventText = QObject::tr("Finished downloading %1.").arg(event->fileName());
            break;
        case FileTransferChatEvent::Initiated :
                eventText = QObject::tr("Incoming file transfer: %1.").arg(event->fileName());
            break;
        case FileTransferChatEvent::Aborted :
                eventText = QObject::tr("Aborted downloading %1.").arg(event->fileName());
            break;
    }

    return QString("<span style=\"color: %1\">").arg(systemMessageColor())
        + QString("[%1] *** %2 </span>").arg(formatTimeStamp(event->timeStamp()), eventText);

}


QString PlainTextChatTheme::createStatusEventPart(const StatusChatEvent * event) const {

    StatusChatEvent::StatusEventType type = event->type;
    QString statusStr;

    switch (type) {
        case StatusChatEvent::Online :
                statusStr = "Online";
            break;
        case StatusChatEvent::Offline :
                statusStr = "Offline";
            break;
        case StatusChatEvent::Away :
                statusStr = "Away";
            break;
        case StatusChatEvent::Xa :
                statusStr = "Not available";
            break;
        case StatusChatEvent::Dnd :
                statusStr = "Do not Disturb";
            break;
        case StatusChatEvent::Chat :
                statusStr = "Free for Chat";
            break;
        case StatusChatEvent::Invisible :
        default:
            statusStr = "Offline";
            break;
    }

    QString color(systemMessageColor());
    QString eventText = QObject::tr("%1 is %2").arg(event->nick(), statusStr);

    if (!event->statusMessage().isEmpty()) {
        eventText += " (" + event->statusMessage() + ")";
    }

    return QString("<span style=\"color: %1\">[%2] ").arg(color, formatTimeStamp(event->timeStamp()))
        + QObject::tr("*** %1 </span>").arg(eventText);
}


QString PlainTextChatTheme::createSystemEventPart(const SystemChatEvent* event) const {

    QString eventText(event->message());

    if (event->type() == SystemChatEvent::EncryptionEnabled) { //append icons
        eventText = "<icon name=\"psi/cryptoYes\"> " + eventText;
    }
    else if (event->type() == SystemChatEvent::EncryptionDisabled) {
        eventText = "<icon name=\"psi/cryptoNo\"> " + eventText;
    }
    
    return QString("<span style=\"color: %1\">").arg(systemMessageColor())
        + QString("[%1] *** %2 </span>").arg(formatTimeStamp(event->timeStamp()), eventText);
}


QString PlainTextChatTheme::formatTimeStamp(const QDateTime &time) const {
    //TODO: provide an option for user to customize time stamp format
    return QString().sprintf("%02d:%02d:%02d", time.time().hour(), time.time().minute(), time.time().second());
}


QString PlainTextChatTheme::colorString(bool local, bool isSpooled) const {
    if (isSpooled) {
        return spooledNickColor();
    }

    if (local) {
        return outgoingNickColor();
    }

    return incomingNickColor();
}


bool PlainTextChatTheme::isValid() {
    return true;
}


QString PlainTextChatTheme::createMoodEventPart(const MoodChatEvent* event) const {
    QString moodText(event->type());

    if (!event->text().isEmpty()) {
        moodText += " (" + event->text() + ")";
    }

    return QString("<span style=\"color: #00A000\">[%1] *** %2 </span>").arg(formatTimeStamp(event->timeStamp()), moodText);
}


QString PlainTextChatTheme::createTuneEventPart(const TuneChatEvent* event) const {
    QString tuneText(event->title());

    if (!event->artist().isEmpty()) {
        tuneText = event->artist() + " - " + tuneText;
    }

    tuneText = QObject::tr("%1 is listeing to %2").arg(event->nick(), tuneText);

    return QString("<span style=\"color: #00A000\">[%1] *** %2 </span>").arg(formatTimeStamp(event->timeStamp()), tuneText);

}


QFont PlainTextChatTheme::chatFont() const {
    return chatFont_;
}


void PlainTextChatTheme::setChatFont(const QFont& chatFont) {
    chatFont_ = chatFont;
}


QString PlainTextChatTheme::incomingNickColor() const {
    return incomingNickColor_;
}


void PlainTextChatTheme::setIncomingNickColor(const QString& incomingNickColor) {
    incomingNickColor_ = incomingNickColor;
}


QString PlainTextChatTheme::outgoingNickColor() const {
    return outgoingNickColor_;
}


void PlainTextChatTheme::setOutgoingNickColor(const QString& outgoingNickColor) {
    outgoingNickColor_ = outgoingNickColor;
}


QString PlainTextChatTheme::spooledNickColor() const {
    return spooledNickColor_;
}


void PlainTextChatTheme::setSpooledNickColor(const QString& spooledNickColor) {
    spooledNickColor_ = spooledNickColor;
}


QString PlainTextChatTheme::systemMessageColor() const {
    return systemMessageColor_;
}


void PlainTextChatTheme::setSystemMessageColor(const QString& systemMessageColor) {
    systemMessageColor_ = systemMessageColor;
}


bool PlainTextChatTheme::useChatSaysStyle() const {
    return useChatSaysStyle_;
}


void PlainTextChatTheme::setUseChatSaysStyle(bool useChatSaysStyle) {
    useChatSaysStyle_ = useChatSaysStyle;
}


bool PlainTextChatTheme::operator==(const PlainTextChatTheme& other) const {
    return ( chatFont_ == other.chatFont_ &&
        incomingNickColor_ == other.incomingNickColor_ &&
        outgoingNickColor_ == other.outgoingNickColor_ &&
        spooledNickColor_ == other.spooledNickColor_ &&
        systemMessageColor_ == other.systemMessageColor_ &&
        useChatSaysStyle_ == other.useChatSaysStyle_);
}


bool PlainTextChatTheme::operator!=(const PlainTextChatTheme& other) const {
    return !(*this == other);
}
