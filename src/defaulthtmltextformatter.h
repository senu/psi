#ifndef _DEFAULTHTMLTEXTFORMATTER_H
#define	_DEFAULTHTMLTEXTFORMATTER_H

#include "htmltextformatter.h"


/** 
 * Default HTMLTextFormatter for HTMLChatView and PlainTextChatView.
 *
 * It should be called 'PsiTextFormatter'.
 *
 * it can: linkify, emoticonify, doLegacyFromatting 
 * and highlight message (eg. for direct messages in MUC)
 */
class DefaultHTMLTextFormatter : public HTMLTextFormatter {

public:


    /** 
     * Specify what kind of formatting TextFormatter should perform
     *
     * \param useImgTagInEmoticonify should be true for HTMLChatView and false for PlainTextChatView
     */
    DefaultHTMLTextFormatter(bool doEmoticonify, bool doLinkify, bool doLegacyFormatting, bool useImgTagInEmoticonify)
    : doEmoticonify_(doEmoticonify),
    doLinkify_(doLinkify),
    doLegacyFormatting_(doLegacyFormatting),
    doHighlighting_(false), 
    useImgTagInEmoticonify_(useImgTagInEmoticonify) {
        
    };


    QDomNode format(const QString& input, const QDomNode& parentElement) const;
    
    /** Returns doLinkify */
    bool doLinkify() const;

    /** Sets doLinkify */
    void setDoLinkify(bool doLinkify);

    /** Returns doEmoticonify */
    bool doEmoticonify() const;

    /** Sets doEmoticonify */
    void setDoEmoticonify(bool doEmoticonify);

    /** Returns doLegacyFormatting */
    bool doLegacyFormatting() const;

    /** Sets doLegacyFormatting */
    void setDoLegacyFormatting(bool doLegacyFormatting);
    
    /** Returns doHighlighting */
    bool doHighlighting() const;

    /** Sets doHighlighting */
    void setDoHighlighting(bool doHighlighting);


protected:
    bool doEmoticonify_;
    bool doLinkify_;
    bool doLegacyFormatting_;
    bool doHighlighting_;
    bool useImgTagInEmoticonify_;

};

#endif	

