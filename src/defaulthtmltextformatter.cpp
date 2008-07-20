#include "defaulthtmltextformatter.h"


QString DefaultHTMLTextFormatter::format(const QString& input, const QString& parentTag) const {
    return input + "XXX";
}


bool DefaultHTMLTextFormatter::doLegacyFormatting() const {
    return doLegacyFormatting_;
}


void DefaultHTMLTextFormatter::setDoLegacyFormatting(bool doLegacyFormatting) {
    doLegacyFormatting_ = doLegacyFormatting;
}


bool DefaultHTMLTextFormatter::doEmoticonify() const {
    return doEmoticonify_;
}


void DefaultHTMLTextFormatter::setDoEmoticonify(bool doEmoticonify) {
    doEmoticonify_ = doEmoticonify;
}


bool DefaultHTMLTextFormatter::doLinkify() const {
    return doLinkify_;
}


void DefaultHTMLTextFormatter::setDoLinkify(bool doLinkify) {
    doLinkify_ = doLinkify;
}
