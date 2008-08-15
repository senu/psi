#include "defaulthtmltextformatter.h"
#include "textutil.h"
#include  <QDebug>


QString DefaultHTMLTextFormatter::format(const QString& input, const QDomNode& parentElement) {

    QString output(input);
    
    //remove /me from first text node
    if(textNodeNumber_ == 0 && removeEmoteString_ && output.startsWith("/me ")) {         
        qDebug() << "DOM transform: removed /me ";
        output = output.mid(4);
    }

    if (doLinkify_ && parentElement.nodeName() != "a") {
        output = TextUtil::linkify(output);
    }
    if (doEmoticonify_) {
        output = TextUtil::emoticonify(output, useImgTagInEmoticonify_);
    }
    if (doLegacyFormatting_) {
        output = TextUtil::legacyFormat(output);
    }

    //TODO ? 14 it would be nice to have html template that handles highlighting
    if (doHighlighting_) {
        output = "<strong>" + output + "</strong>";
    }

//    qDebug() << "!!! tf messageText1.5 0" << output;

    if (!input.trimmed().isEmpty()) { //skip nodes that contains only whitespaces
        textNodeNumber_++;
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


bool DefaultHTMLTextFormatter::doHighlighting() const {
    return doHighlighting_;
}


void DefaultHTMLTextFormatter::setDoHighlighting(bool doHighlighting) {
    doHighlighting_ = doHighlighting;
}


bool DefaultHTMLTextFormatter::removeEmoteString() const {
    return removeEmoteString_;
}


void DefaultHTMLTextFormatter::setRemoveEmoteString(bool removeEmoteString) {
    removeEmoteString_ = removeEmoteString;
}


int DefaultHTMLTextFormatter::textNodeNumber() const {
    return textNodeNumber_;
}


void DefaultHTMLTextFormatter::setTextNodeNumber(int textNodeNumber) {
    textNodeNumber_ = textNodeNumber;
}
