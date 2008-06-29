#include "statusChatEvent.h"

QString StatusChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
	return theme.createStatusEventPart(this);
}

QString StatusChatEvent::statusMessage() const {
	return _statusMessage;
}


void StatusChatEvent::setStatusMessage(QString statusMessage) {
	_statusMessage = statusMessage;	
}
