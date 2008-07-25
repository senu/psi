#include "defaulthtmltextformatter.h"
#include "textutil.h"


QString DefaultHTMLTextFormatter::format(const QString& input, const QString& parentTag) const {

    if (!doEmoticonify_ && !doLinkify_ && !doLegacyFormatting_) {
        return input;
    }

    QString output(input);

    if (doLinkify_ && parentTag != "a") {
        output = TextUtil::linkify(output);
    }
    if (doEmoticonify_) {
        output = TextUtil::emoticonify(output, true);
    }
    if (doLegacyFormatting_) {
        output = TextUtil::legacyFormat(output);
    }

    return output;
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
