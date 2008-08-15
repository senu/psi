#ifndef _DEFAULTHTMLTEXTFORMATTER_H
#define	_DEFAULTHTMLTEXTFORMATTER_H

#include "htmltextformatter.h"


/** 
 * Default HTMLTextFormatter for HTMLChatView and PlainTextChatView.
 *
 * It should be called 'PsiTextFormatter'.
 *
 * It can: linkify, emoticonify, doLegacyFromatting 
 * and highlight message (eg. for direct messages in MUC)
 *
 * You have to reset textNodeNumber everytime you call MessageValidator::validateMessage() 
 * with this textFormatter.
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
    useImgTagInEmoticonify_(useImgTagInEmoticonify),
    removeEmoteString_(false),
    textNodeNumber_(0) {

    };


    QString format(const QString& input, const QDomNode& parentElement);

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

    /** Returns removeEmoteString */
    bool removeEmoteString() const;

    /** Sets removeEmoteString */
    void setRemoveEmoteString(bool removeEmoteString);

    /** Returns textNodeNumber */
    int textNodeNumber() const;

    /** Sets textNodeNumber */
    void setTextNodeNumber(int textNodeNumber);



protected:
    bool doEmoticonify_;
    bool doLinkify_;
    bool doLegacyFormatting_;
    bool doHighlighting_;
    bool useImgTagInEmoticonify_;

    /** This property holds whether '/me' substring should be deleted from the first text node*/
    bool removeEmoteString_;

    /**
     * This this variable is used to count text nodes (preorder). 
     * We count nodes from 0. 
     *
     * Nodes containg whitespaces aren't counted.
     */
    int textNodeNumber_;
};

#endif	

