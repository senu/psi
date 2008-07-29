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
 */
class MessageValidator {

public:
    MessageValidator();
    ~MessageValidator();

    /**
     * Returns new (valid) XHTML message; 
     * \param modified is set to true if message was modified 
     * \formatter will be used to format text conntent 
     */
    QString validateMessage(QString message, bool* modified, const HTMLTextFormatter* formatter);

protected:
    //TODO stack instead of recursion?
    //OK -> textNode, node we want to delete, textNode2 --delete--> != textNode + textNode2 


    /** per-Node structure used in XHTML-IM validation */
    struct NodeInfo {

        NodeInfo();

        /** Allowed direct child elements*/
        QStringList allowedTags;

        /** Allowed tag attributes */
        QStringList allowedAttributes;

        /** Can have text child - eg. false for <br> */
        bool canHaveText;

        bool canBeEmpty; //TODO unused. Do we need that?
    };

    /**
     * Traverse through Tree(cur) and cut off bad elements/attributes/styles.
     * \param modified will be set to true if tree was modified
     * \param formatter will be used as a TextFormatter
     */
    void dfs(QDomElement cur, const HTMLTextFormatter* formatter, bool* modified);

    /** Fills allowed dictionary */
    void generateAllowedDict();

    /** Converts const QString array to QStringList, arraySize is sizeof(QString)*n_elements we want to add */
    void appendArrayToList(const QString *array, int arraySize, QStringList& list);

    /** Tag name -> NodeInfo dict */
    QHash<QString, NodeInfo> allowed;



};



#endif	/* _MESSAGEVALIDATOR_H */

