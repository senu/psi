#include "htmlChatTemplate.h"

#include <QtDebug>

HTMLChatTemplate::HTMLChatTemplate(const QString _content) 
	: content(_content) {}


HTMLChatPart HTMLChatTemplate::createFreshHTMLPart() const {
	return HTMLChatPart(content);
}

