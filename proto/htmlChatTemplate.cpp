#include "htmlChatTemplate.h"

#include <QtDebug>

HTMLChatTemplate::HTMLChatTemplate(const QString content) 
	: _content(_content) {}


QString HTMLChatTemplate::content() const {
	return _content;
}

void HTMLChatTemplate::setContent(QString content) {
	_content = content;
}

HTMLChatPart HTMLChatTemplate::createFreshHTMLPart() const {
	return HTMLChatPart(content());
}

