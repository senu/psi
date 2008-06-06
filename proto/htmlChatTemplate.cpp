#include "htmlChatTemplate.h"


HTMLChatTemplate::HTMLChatTemplate(QString _content) 
	: content(_content) {}


QString HTMLChatTemplate::toString() {
	return content;
}
