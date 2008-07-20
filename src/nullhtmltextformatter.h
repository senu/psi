#ifndef _NULLHTMLTEXTFORMATTER_H
#define	_NULLHTMLTEXTFORMATTER_H

#include "htmltextformatter.h"


/** HTMLTextFormatter that outputs input */
class NullHTMLTextFormatter : public HTMLTextFormatter {

public:



    /** Returns \param input */
    QString format(const QString& input, const QString& parentTag) const {
        return input;
    }


};

#endif

