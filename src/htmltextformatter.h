#ifndef _HTMLTEXTFORMATTER_H
#define	_HTMLTEXTFORMATTER_H

#include <QString>
#include <QDomNode>


/**
 * Abstract TextFormatter is used when MessageValidator encounters text node in DOM tree.
 *
 * You can iconify, linkify, etc. message body here.
 *
 * Everytime MessageValidator encounters text node T it wil replace T with ::format(T).
 *
 * TextFormatter and MessageValidator can be easily modified to format other DOM nodes, 
 * for example, formatNode(<p>text</p>) = [text, <br/>]
 */
class HTMLTextFormatter {

public:


    /**
     * Formats XHTML-IM text node and returns formated xml fragment (QString).
     *
     * formats \param input which is a text child of \param parenteElement 
     * 
     * Some may wonder why QString is returned (eg. "<b>text</b>") instead of QDomNodeList - 
     * it's a long story (performance issues, missing spaces, unclean code).
     */
    virtual QString format(const QString& input, const QDomNode& parentElement) = 0;


    virtual ~HTMLTextFormatter() {
    };

};


#endif

