
#include <QtXml>

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

// http://www.w3.org/TR/CSS21/syndata.html#syntax
// http://www.w3.org/TR/CSS21/grammar.html
// CSS is validated in JavaScript code with Webkit 

//TODO static


void MessageValidator::dfs(QDomElement cur, const HTMLTextFormatter* formatter, bool* modified) {

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
            *modified = true;
            i--;
        }
    }

    QDomNodeList children = cur.childNodes();

    for (int i = 0; i < children.size(); i++) {
        QDomNode node = children.at(i);

        if (node.isElement()) {
            QString childName = node.toElement().tagName();

            if (childName == "style") { //this action is not XHTML-IM compliant!
                cur.removeChild(node);
                *modified = true;
                i--;
            }
            else if (!curNI.allowedTags.contains(childName)) {//is subElement valid here?

                //qDebug() << "VALIDATIN ERR" << "TS" << childName << " in " << parentName;
                //qDebug() << "note allowed subElements are:" << curNI.allowedTags;

                //append bad node's children (they will be walidated in next loop iteration)
                while (node.hasChildNodes()) {
                    cur.insertBefore(node.firstChild(), node);
                }

                //delete bad node
                cur.removeChild(node);
                *modified = true;
                i--;
            }
            else {
                dfs(node.toElement(), formatter, modified);
            }
        }
        else if (node.isText() && !node.isCDATASection()) {
            if (!curNI.canHaveText) {
                cur.removeChild(node);
                *modified = true;
                i--;
            }
            else { //format text
                QDomNode newElement = formatter->format(node.toText().data(), cur);
                QDomNode node2 = cur.replaceChild(newElement, node); //TODO remove node2
            }
        }
    }


}


MessageValidator::MessageValidator() {

    generateAllowedDict();

}


MessageValidator::~MessageValidator() {

}


void MessageValidator::generateAllowedDict() {
    //TODO check XHTML rfc 

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
    for (int i = 0; i< sizeof (textElements) / sizeof (QString); i++) {
        allowed[textElements[i]] = textNI;
    }

    for (int i = 0; i< sizeof (structureElements) / sizeof (QString); i++) {
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
    for (int i = 0; i < arraySize / sizeof (QString); i++) {
        list.append(array[i]);
    }
}


QString MessageValidator::validateMessage(QString message, bool* modified, const HTMLTextFormatter* formatter) {

    QDomDocument doc("document");

    QString errorMessage;
    int line, column;
    *modified = false;

    if (!doc.setContent(message, false, &errorMessage, &line, &column)) {
        qDebug() << errorMessage << " " << line << " " << column << message;
        *modified = true;
        return "illformed message!!!"; //TODO - display plain message
    }

    dfs(doc.documentElement(), formatter, modified);
    return doc.toString(0);
}


MessageValidator::NodeInfo::NodeInfo() {
    canBeEmpty = true;
    canHaveText = true;
}
