#ifndef _HTMLTEXTFORMATTER_H
#define	_HTMLTEXTFORMATTER_H

#include <QString>
#include <QDomNode>


/**
 * Abstract TextFormatter is used when MessageValidator encounters text node in DOM tree.
 * You can iconify/linkify/etc message body here  */
class HTMLTextFormatter {

public:


    /**
     * Formats xhtml-im text node and return it as a QDomNode
     *
     * formats \param input a text child of \param ParentTag */
    virtual QDomNode format(const QString& input, const QDomNode& parentElement) const = 0;


    virtual ~HTMLTextFormatter() {
    };

};


#endif

