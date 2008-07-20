#ifndef _DEFAULTHTMLTEXTFORMATTER_H
#define	_DEFAULTHTMLTEXTFORMATTER_H

#include "htmltextformatter.h"

/** HTMLTextFormatter for HTMLChatView */
class DefaultHTMLTextFormatter : public HTMLTextFormatter {

public:


    /** 
     * Specify what kind of formatting TextFormatter should perform
     */
    DefaultHTMLTextFormatter(bool doEmoticonify, bool doLinkify, bool doLegacyFormatting)
    : doEmoticonify_(doEmoticonify), doLinkify_(doLinkify), doLegacyFormatting_(doLegacyFormatting){
    };


    QString format(const QString& input, const QString& parentTag) const;

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
    
private:
    bool doEmoticonify_;
    bool doLinkify_;
    bool doLegacyFormatting_;

};

#endif	

