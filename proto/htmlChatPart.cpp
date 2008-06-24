#include "htmlChatPart.h"

HTMLChatPart::HTMLChatPart(const QString _content) 
	: content(_content) {}


QString HTMLChatPart::toString() {
	return content;
}

void HTMLChatPart::replaceAndEscapeKeyword(QString keyword, QString value) {
	content.replace(keyword,escapeString(value));
	qDebug() << content;
}

QString HTMLChatPart::escapeString(QString string) {
	return string.replace('"', "\"");
} 
