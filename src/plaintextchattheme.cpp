#include "plaintextchattheme.h"


PlainTextChatTheme::PlainTextChatTheme() {

}


QString PlainTextChatTheme::createEmoteEventPart(const EmoteChatEvent * event) const {
    QString color = colorString(event->isLocal(), event->isSpooled());
    return QString("<span style=\"color: %1\">").arg(color)
            + QString("[%1]").arg(formatTimeStamp(event->timeStamp()))
            + QString(" *%1 ").arg(event->nick())
            + event->message() + "</span>";
}


QString PlainTextChatTheme::createIncomingMessagePart(const MessageChatEvent *) const {
}


QString PlainTextChatTheme::createOutgoingMessagePart(const MessageChatEvent *) const {
}


QString PlainTextChatTheme::createFileTransferEventPart(const FileTransferChatEvent * event) const {
}


QString PlainTextChatTheme::createStatusEventPart(const StatusChatEvent * event) const {
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
