#ifndef _HTMLTEXTFORMATTER_H
#define	_HTMLTEXTFORMATTER_H

#include <QString>


/**
 * Abstract TextFormatter is used when MessageValidator encounters text node in DOM tree.
 * You can iconify/linkify/etc message body here  */
class HTMLTextFormatter {

public:


    /** Return formatted string for \paraminput whose partent is \param ParentTag */
    virtual QString format(const QString& input, const QString& parentTag) const = 0;


    virtual ~HTMLTextFormatter() {
    };

};


#endif

