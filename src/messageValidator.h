#ifndef _MESSAGEVALIDATOR_H
#define	_MESSAGEVALIDATOR_H

#include <QString>
#include <QStringList>
#include <QtDebug>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QHash>
#include <QPair>

#include "htmltextformatter.h"


/** 
 * Performs XHTML-IM message validation (and cuts off bad elements/attributes). 
 *
 * It also can modify message (e.g emoticonify, linkify) - see HTMLTextFormatter
 *
 * http://www.w3.org/TR/CSS21/syndata.html#syntax
 * http://www.w3.org/TR/CSS21/grammar.html         
 * 
 * //TODO I would have to learn flex/bison/? to do that here ->
 * CSS is validated by JavaScript code with Webkit 
 *
 */
class MessageValidator {

public:
    MessageValidator();
    ~MessageValidator();

    /**
     * Returns new (valid) XHTML message; 
     *
     * \param illformed is set to true if message was illformed (couldn't be parsed)
     * \param formatter will be used to format text conntent. 
     *
     * formatter is not const pointer. You can modify it in HTMLTextFormatter::format()
     * format() is called for every DOM text node in preorder format.
     *  
     */
    QString validateMessage(QString message, bool* illformed, HTMLTextFormatter* formatter);

protected:

    /** per-Node structure used in XHTML-IM validation */
    struct NodeInfo {

        NodeInfo();

        /** Allowed direct child elements*/
        QStringList allowedTags;

        /** Allowed tag attributes */
        QStringList allowedAttributes;

        /** Can have text child - eg. false for <br> */
        bool canHaveText;

        //bool canBeEmpty;
    };

    /** Fills allowed dictionary */
    void generateAllowedDict();

    /** Converts const QString array to QStringList, arraySize is sizeof(QString)*n_elements we want to add */
    void appendArrayToList(const QString *array, int arraySize, QStringList& list);

    /** Tag name -> NodeInfo dict */
    QHash<QString, NodeInfo> allowed;



};



#endif	/* _MESSAGEVALIDATOR_H */

