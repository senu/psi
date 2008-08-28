#include <QRegExp>
#include <QColor>
#include <QDateTime>
#include <ctime> //time

#include "htmlchatpart.h"


HTMLChatPart::HTMLChatPart(const QString content_)
: content(content_) {
}


HTMLChatPart::HTMLChatPart() {
};


QString HTMLChatPart::toString() const {
    return content;
}


void HTMLChatPart::replaceAndEscapeKeyword(QString keyword, QString value) {
    content.replace(keyword, escapeString(value));
}


void HTMLChatPart::replaceMessageBody(QString value) {
    messageBody_ = escapeString(value);
}


QString HTMLChatPart::escapeString(QString string) {
    return string; //replace('\\', "\\\\").replace('%', "\\%");
}


void HTMLChatPart::replaceTimeKeyword(QString keyword, QDateTime time) {
    QRegExp timePattern("%" + keyword + "\\{([^}]*)\\}%");

    for (int pos = 0; (pos = timePattern.indexIn(content, pos)) != -1;) {
        QString timeString = formatTime(timePattern.cap(1), time);
        content.replace(pos, timePattern.cap(0).length(), timeString);
    }
}


void HTMLChatPart::replaceSenderColorKeyword(const QColor& userColor) {

    QRegExp colorPattern("%senderColor(?:\\{([^}]*)\\})?%");
    QString colorString = userColor.name();

    for (int pos = 0; (pos = colorPattern.indexIn(content, pos)) != -1;) {
        bool doLight = colorPattern.numCaptures() > 0;
        if (doLight) {
            int factor = colorPattern.cap(1).toUInt(&doLight);

            if (doLight) {
                colorString = userColor.lighter(factor).name();
            }
        }

        content.replace(pos, colorPattern.cap(0).length(), colorString);
    }
}


QString HTMLChatPart::formatTime(QString format, const QDateTime& time) {
    char buff[256];

    time_t timet = time.toTime_t();
    strftime(buff, 256, format.toAscii().data(), localtime(&timet));

    return QString(buff);
}


QString HTMLChatPart::createShortTime(const QDateTime& time) {
    return time.toString("hh:mm");
}


QString HTMLChatPart::messageBody() const {
    return messageBody_;
}
