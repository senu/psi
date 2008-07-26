#ifndef _NULLHTMLTEXTFORMATTER_H
#define	_NULLHTMLTEXTFORMATTER_H

#include "htmltextformatter.h"
#include <QDomText> 


/** HTMLTextFormatter that outputs input */
class NullHTMLTextFormatter : public HTMLTextFormatter {

public:

    QDomNode format(const QString& input, const QDomNode& parentElement) const {
        QDomText node;
        node.setData(input);
    }
};

#endif

