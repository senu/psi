#include "htmlchattemplate.h"

HTMLChatTemplate::HTMLChatTemplate(const QString content)
: content_(content_) {
}

HTMLChatTemplate::HTMLChatTemplate(const HTMLChatTemplate& other) {
    content_ = other.content_;
}


QString HTMLChatTemplate::content() const {
    return content_;
}


void HTMLChatTemplate::setContent(QString content) {
    content_ = content;
}


HTMLChatPart HTMLChatTemplate::createFreshHTMLPart() const {
    return HTMLChatPart(content());
}

