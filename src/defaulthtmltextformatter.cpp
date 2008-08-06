#include "defaulthtmltextformatter.h"
#include "textutil.h"
#include  <QDebug>


QDomNode DefaultHTMLTextFormatter::format(const QString& input, const QDomNode& parentElement) const {

    QString output(input);
    

    if (doLinkify_ && parentElement.nodeName() != "a") {
        output = TextUtil::linkify(output);
    }
    if (doEmoticonify_) {
        output = TextUtil::emoticonify(output, true);
    }
    if (doLegacyFormatting_) {
        output = TextUtil::legacyFormat(output);
    }

    //TODO ? 14 it would be nice to have html template that handles highlighting
    if (doHighlighting_) {
        output = "<strong>" + output + "</strong>";
    }


    QDomDocument node;
    qDebug() << "!!! tf messageText1.5 0" << output;
    node.setContent("<span>"+output+"</span>");

    return node.firstChild();
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
