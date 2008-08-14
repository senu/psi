#ifndef _HTMLTEXTFORMATTER_H
#define	_HTMLTEXTFORMATTER_H

#include <QString>
#include <QDomNode>


/**
 * Abstract TextFormatter is used when MessageValidator encounters text node in DOM tree.
 * You can iconify/linkify/etc message body here .
 */
class HTMLTextFormatter {

public:


    /**
     * Formats xhtml-im text node and return formated xml fragment (QString)
     *
     * formats \param input which is a text child of \param parenteElement 
     * 
     * Some may wonder why QString is returned (eg. "<b>text</b>") not QDomNode, 
     * it's a long story (performance issues, missing spaces, unclean code).
     */
    virtual QString format(const QString& input, const QDomNode& parentElement) = 0;


    virtual ~HTMLTextFormatter() {
    };

};


#endif

