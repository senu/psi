#include <QtXml>
#include <QStack>
#include <QTextDocument> //qt escape


#include "messageValidator.h"
#include "messagechatevent.h"
#include "nullhtmltextformatter.h"


//Elements
const QString structureElements[] = {
    "body", "html", "head", "title"
};

const QString textElements[] = {
    "abbr", "acronym", "address", "blockquote", "br", "cite",
    "code", "dfn", "div", "em", "h1", "h2", "h3", "h4", "h5",
    "h6", "kbd", "p", "pre", "q", "samp", "span", "strong", "var"
};

const QString hypertextElements[] = {
    "a"
};

const QString imgElements[] = {
    "img"
};

const QString listElements[] = {
    "dl", "dt", "dd", "li", "ol", "ul"
};

//Attributes 
const QString defaultAttributes[] = {
    "class", "id", "title", "style"
};

const QString citeAttributes[] = {
    "class", "id", "title", "style", "cite"
};

const QString hypertextAttributes[] = {
    "class", "id", "title", "style",
    "accesskey", "charset", "href", "hreflang",
    "rel", "rev", "tabindex", "type"
};

const QString imgAttributes[] = {
    "class", "id", "title", "style", "alt", "height",
    "longdesc", "src", "width"
};
const QString headAttributes[] = {
    "profile"
};

const QString htmlAttributes[] = {
    "version"
};

//styles
const QString styleProperties[] = {
    "background-color", "color", "font-family", "font-size", "font-style",
    "font-weight", "margin-left", "margin-right", "text-align", "text-decoration"
};

QHash<QString, MessageValidator::NodeInfo> MessageValidator::allowed = QHash<QString, MessageValidator::NodeInfo>();


MessageValidator::MessageValidator() {
    if (allowed.isEmpty()) {
        generateAllowedDict();
    } //else - allowed is static so it was generated before
}


MessageValidator::~MessageValidator() {

}


void MessageValidator::generateAllowedDict() {

    NodeInfo textNI,
        hypertextNI,
        imgNI,
        structNI,
        listNI;


    appendArrayToList(textElements, sizeof (textElements), structNI.allowedTags);
    appendArrayToList(listElements, sizeof (listElements), structNI.allowedTags);
    appendArrayToList(hypertextElements, sizeof (hypertextElements), structNI.allowedTags);
    appendArrayToList(imgElements, sizeof (imgElements), structNI.allowedTags);

    appendArrayToList(textElements, sizeof (textElements), textNI.allowedTags);
    appendArrayToList(listElements, sizeof (listElements), textNI.allowedTags);
    appendArrayToList(hypertextElements, sizeof (hypertextElements), textNI.allowedTags);
    appendArrayToList(imgElements, sizeof (imgElements), textNI.allowedTags);

    appendArrayToList(textElements, sizeof (textElements), hypertextNI.allowedTags);

    //attrs
    appendArrayToList(defaultAttributes, sizeof (defaultAttributes), textNI.allowedAttributes);
    appendArrayToList(imgAttributes, sizeof (imgAttributes), imgNI.allowedAttributes);
    appendArrayToList(hypertextAttributes, sizeof (hypertextAttributes), hypertextNI.allowedAttributes);

    //fill allowed dict
    for (unsigned int i = 0; i< sizeof (textElements) / sizeof (QString); i++) {
        allowed[textElements[i]] = textNI;
    }

    for (unsigned int i = 0; i< sizeof (structureElements) / sizeof (QString); i++) {
        allowed[structureElements[i]] = structNI;
    }

    //misc
    hypertextNI.allowedTags.append("img");

    allowed["html"].allowedTags.append("body");
    allowed["html"].allowedTags.append("head");

    allowed["head"].allowedTags.append("title");

    allowed["body"].allowedAttributes.append("style");
    allowed["body"].allowedAttributes.append("class");
    allowed["body"].allowedAttributes.append("id");
    allowed["body"].allowedAttributes.append("title");

    allowed["br"].canHaveText = false;

    allowed["blockquote"].allowedAttributes.append("cite");
    allowed["q"].allowedAttributes.append("cite");

    allowed["img"] = imgNI;
    allowed["a"] = hypertextNI;
}


void MessageValidator::appendArrayToList(const QString *array, int arraySize, QStringList& list) {
    for (unsigned int i = 0; i < arraySize / sizeof (QString); i++) {
        list.append(array[i]);
    }
}


QString MessageValidator::validateMessage(QString message, bool* illformed, HTMLTextFormatter* formatter) {

//    qDebug() << "IMG val0" << message;
    QDomDocument doc("document");
    *illformed = false;

    QString errorMessage;
    int line, column;

    if (!doc.setContent(message, false, &errorMessage, &line, &column)) {
        qDebug() << errorMessage << " " << line << " " << column << message;
        *illformed = true;
        qDebug() << "WARNING: MessageValidator::validateMessage() - illformed message";
        return "illformed message!!!";
    }

    //now DOM tree will be traversed in preorder. 
    QStack<QDomElement> stack; //current element, QStack is used to avoid possible stack overflow in ordinary recursion
    stack.push(doc.documentElement());

    while (!stack.empty()) {
        QDomElement cur = stack.top();
        stack.pop();

        // Traverse through DOM Tree(cur), cut off bad elements/attributes 
        // and format text nodes using textFormatter

        //    qDebug() << QString(4, ' ') << cur.tagName();

        QString parentName = cur.tagName();
        NodeInfo curNI = allowed[parentName];

        //delete disallowed attributes
        for (int i = 0; i < cur.attributes().count(); i++) {
            QString attrName = cur.attributes().item(i).toAttr().name();

            if (!curNI.allowedAttributes.contains(attrName)) {
                //     qDebug() << "VALIDATIN ERR" << "TA" << attrName  << " in " << parentName;
                //   qDebug() << "note allowed attributes are:" << curNI.allowedAttributes;

                cur.attributes().removeNamedItem(attrName);
                i--;
            }
        }

        QDomNodeList children = cur.childNodes();

        for (int i = children.size() - 1; i >= 0; i--) {
            QDomNode node = children.at(i);

            if (node.isElement()) {
                QString childName = node.toElement().tagName();

                if (childName == "a") { // always show hyperlink destination
                    QString href = node.toElement().attribute("href");
                    node.appendChild(doc.createTextNode(" [ " + href + " ]")); 
                }
                
                if (childName == "style") { //NOTE: this action is not XHTML-IM compliant! (css rules should be displayed, but it's stupid)
                    cur.removeChild(node);
                }
                else if (childName == "img") { //disabling images until they are whitelisted

                    QString href = node.toElement().attribute("src");
                    
                    QDomElement newElement = doc.createElement("a");
                    newElement.setAttribute("class", "psi_disabled_image");
                    newElement.setAttribute("href", "javascript:psi_addToWhiteList('" + href + "')");
                    newElement.appendChild(doc.createTextNode("[ click here to display: " + href + " ]"));
                    
                    cur.replaceChild(newElement, node);
                }
                else if (!curNI.allowedTags.contains(childName)) {//is subElement valid here?

                    qDebug() << "VALIDATIN ERR" << "TS" << childName << " in " << parentName;
                    qDebug() << "note allowed subElements are:" << curNI.allowedTags;

                    //append bad node's children (they will be validated in next loop iteration)
                    int j = 0;
                    while (node.hasChildNodes()) {
                        cur.insertBefore(node.firstChild(), node);
                        j++;
                    }

                    i = i + j; //j nodes were inserted

                    //delete bad node
                    cur.removeChild(node);
                }
                else {
                    stack.push(node.toElement());
                    //dfs(node.toElement(), formatter, illformed); //TODO 105 ins
                }
            }
            else if (node.isText() && !node.isCDATASection()) {
                if (!curNI.canHaveText) {
                    cur.removeChild(node);
                }
                else { //format text
                    QDomNode newElement = formatter->format(Qt::escape(node.toText().data()), cur);
                    //NOTE: we don't need to escape quotes, and we want this code be more reusable, 
                    //NOTE: so we use Qt::escape() instead of TextUtil::escape()
                    cur.replaceChild(newElement, node);
                }
            }
        }//foreach child
    } //stack/dfs

//    qDebug() << "IMG" <<  doc.toString(0);
    return doc.toString(0);
}


MessageValidator::NodeInfo::NodeInfo() {
    //canBeEmpty = true;
    canHaveText = true;
}
