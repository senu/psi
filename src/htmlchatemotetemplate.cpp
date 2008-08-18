#include "htmlchatemotetemplate.h"


HTMLChatEmoteTemplate::HTMLChatEmoteTemplate() : HTMLChatTemplate(), isEmoteTemplate_(false) {
};


HTMLChatEmoteTemplate::HTMLChatEmoteTemplate(QString content) : HTMLChatTemplate(content), isEmoteTemplate_(false) {
};


bool HTMLChatEmoteTemplate::isEmoteTemplate() const {
    return isEmoteTemplate_;
}


void HTMLChatEmoteTemplate::setEmoteTemplate(bool is) {
    isEmoteTemplate_ = is;
}
