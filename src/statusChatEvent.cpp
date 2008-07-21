#include "statusChatEvent.h"


QString StatusChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createStatusEventPart(this);
}


QString StatusChatEvent::statusMessage() const {
    return statusMessage_;
}


void StatusChatEvent::setStatusMessage(QString statusMessage) {
    statusMessage_ = statusMessage;
}
