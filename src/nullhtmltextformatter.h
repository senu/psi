#ifndef _NULLHTMLTEXTFORMATTER_H
#define	_NULLHTMLTEXTFORMATTER_H

#include "htmltextformatter.h"


/** HTMLTextFormatter that outputs input */
class NullHTMLTextFormatter : public HTMLTextFormatter {

public:


    QString format(const QString& input, const QDomNode& parentElement) {
        return input;
    }
};

#endif

