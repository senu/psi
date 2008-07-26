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

    //if (PsiOptions::instance()->getOption("options.ui.chat.use-chat-says-style").toBool()) { //TODO
    if (0) {
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

    QString eventText(event->statusMessage());
    QString color("#00A000");

    if(!eventText.isEmpty()) {
        eventText = " (" + eventText + ")";
    }
   
    qDebug() << "status event" << statusStr;
    return QString("<span style=\"color: %1\">[%2] ").arg(color,formatTimeStamp(event->timeStamp()))
        + QObject::tr("*** %2 is %3 </span>").arg(event->nick(), eventText);
}


QString PlainTextChatTheme::createSystemEventPart(const SystemChatEvent* event) const {

    QString color = "#00A000";
    return QString("<span style=\"color: %1\">").arg(color)
        + QString("[%1] *** %2 </span>").arg(formatTimeStamp(event->timeStamp()), event->message());
}


QString PlainTextChatTheme::formatTimeStamp(const QDateTime &time) const {
    //TODO: provide an option for user to customize time stamp format
    //TODO ask kev QDateTime::toString() ?
    return QString().sprintf("%02d:%02d:%02d", time.time().hour(), time.time().minute(), time.time().second());
}


QString PlainTextChatTheme::colorString(bool local, bool isSpooled) const {
    if (isSpooled)
        return "#008000";

    if (local)
        return "#FF0000";

    return "#0000FF";
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