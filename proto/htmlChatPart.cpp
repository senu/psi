#include <QRegExp>
#include "htmlChatPart.h"


HTMLChatPart::HTMLChatPart(const QString _content)
: content(_content) {
}


QString HTMLChatPart::toString() {
    return content;
}


void HTMLChatPart::replaceAndEscapeKeyword(QString keyword, QString value) {
    content.replace(keyword, escapeString(value));
    qDebug() << content;
}

void HTMLChatPart::replaceMessageBody(QString value) {
	_messageBody = escapeString(value);
} 


QString HTMLChatPart::escapeString(QString string) {
    return string.replace('"', "\"");
}


void HTMLChatPart::replaceTimeKeyword(QString keyword, QDateTime time) {
    QRegExp timePattern("%" + keyword + "\\{([^}]*)\\}%");

    for (int pos = 0; (pos = timePattern.indexIn(content, pos)) != -1;) {
        QString timeString = formatTime(timePattern.cap(1), time);
        content.replace(pos, timePattern.cap(0).length(), timeString);
    }
}


QString HTMLChatPart::formatTime(QString format, QDateTime time) {
    char buff[256];

    time_t timet = time.toTime_t();
    strftime(buff, 256, format.toAscii().data(), localtime(&timet));

    return QString(buff);
}

QString HTMLChatPart::messageBody() const {
	return _messageBody;
}