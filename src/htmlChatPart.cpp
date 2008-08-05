#include <QRegExp>
#include <QColor>
#include <QDateTime>
#include <ctime> //time
#include "htmlChatPart.h"


HTMLChatPart::HTMLChatPart(const QString _content)
: content(_content) {
}


QString HTMLChatPart::toString() {
    return content;
}


void HTMLChatPart::replaceAndEscapeKeyword(QString keyword, QString value) {
    content.replace(keyword, escapeString(value));
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



// These colors are used for coloring nicknames. I tried to use
// colors both visible on light and dark background.
// [it's Kopete color list]


void HTMLChatPart::replaceSenderColorKeyword(const QColor& userColor) {
    /* TODO 46 move this to default options 
    static const char* const colorList[] = {
        "red", "blue", "gray", "magenta", "violet", "#808000", "yellowgreen",
        "darkred", "darkgreen", "darksalmon", "darkcyan", "#B07D2B", "mediumpurple",
        "peru", "olivedrab", "#B01712", "darkorange", "slateblue", "slategray",
        "goldenrod", "orangered", "tomato", "#1E90FF", "steelblue", "deeppink",
        "saddlebrown", "coral", "royalblue"
    };
   */

    QRegExp colorPattern("%senderColor(?:\\{([^}]*)\\})?%");
    QString colorString;

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
    return _messageBody;
}
