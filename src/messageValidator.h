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


/** Performs XHTML-IM message validation (and cuts off bad elements/attributes) */
class MessageValidator {

public:
    MessageValidator();
    ~MessageValidator();

    /** Returns new (valid) XHTML message; modified is set to true if message was modified */
    QString validateMessage(QString message, bool* modified);

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

	/** Traverse through Tree(cur) and cut off bad elements/attributes/styles.
		tabs are for debug;
		modified will be set to true if tree was modified
	 */
    void dfs(QDomElement cur, int tabs, bool* modified);

    /** Fills allowed dictionary */
    void generateAllowedDict();

    /** Converts const QString array to QStringList, arraySize is sizeof(QString)*n_elements we want to add */
	void appendArrayToList(const QString *array, int arraySize, QStringList& list);

    /** Tag name -> NodeInfo dict */
    QHash<QString, NodeInfo> allowed;



};



#endif	/* _MESSAGEVALIDATOR_H */
