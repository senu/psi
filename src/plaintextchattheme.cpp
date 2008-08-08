#include "plaintextchattheme.h"
#include <QDebug> 


PlainTextChatTheme::PlainTextChatTheme() {

}


QString PlainTextChatTheme::createEmoteEventPart(const EmoteChatEvent * event) const {

    QString color = colorString(event->isLocal(), event->isSpooled());

    return QString("<span style=\"color: %1\">").arg(color)
        + QString("[%1]").arg(formatTimeStamp(event->timeStamp()))
        + QString(" *%1 ").arg(event->nick())
        + event->message() + "</span>";
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
    //TODO 72
}


QString PlainTextChatTheme::createStatusEventPart(const StatusChatEvent * event) const {

    StatusChatEvent::StatusEventType type = event->type;
    QString statusStr;

    switch (type) {
        case StatusChatEvent::Online :
                statusStr = "online";
            break;
        case StatusChatEvent::Offline :
                statusStr = "offline";
            break;
        case StatusChatEvent::Away :
                statusStr = "idle";
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
        case StatusChatEvent::Invisible :
        default:
                statusStr = "offline";
            break;
    }

    QString eventText(event->statusMessage());
    QString color(systemMessageColor());

    if (!eventText.isEmpty()) {
        eventText = " (" + eventText + ")";
    }

    qDebug() << "status event" << statusStr;
    return QString("<span style=\"color: %1\">[%2] ").arg(color, formatTimeStamp(event->timeStamp()))
        + QObject::tr("*** %2 is %3 </span>").arg(event->nick(), eventText);
}


QString PlainTextChatTheme::createSystemEventPart(const SystemChatEvent* event) const {

    return QString("<span style=\"color: %1\">").arg(systemMessageColor())
        + QString("[%1] *** %2 </span>").arg(formatTimeStamp(event->timeStamp()), event->message());
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



