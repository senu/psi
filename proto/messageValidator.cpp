
#include <QtXml>

#include "messageValidator.h"
#include "chatMessageEvent.h"


//Elements
const QString structureElements[] = {
    "body", "html", "title"
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

//TODO ? validate style values (eg. text-decoderation: underline)?


enum ValidationResult {
    OK,
    Modified,
    Removed
};


typedef QPair<ValidationResult, QDomNode> ValidatedNode;

//TODO:
// 1.  currently <div><script><strong>visible</strong></script></div>  ~~> </div></div>
//
//   but:
//   W3C TEXT: If a user agent encounters an element it does not recognize, it must continue to process the children of that element. If the content is text, the text must be presented to the user.
// 2. We need CSS validation

void MessageValidator::dfs(QDomElement cur, int tabs) {
    tabs += 3;

    qDebug() << QString(tabs, ' ') << cur.tagName() << " ---> " << (bool)allowed.contains(cur.tagName());

	QString parentName = cur.tagName();

	NodeInfo curNI = allowed[parentName]; 

	//delete disallowed attributes
	for(int i=0; i < cur.attributes().count(); i++) {
		QString attrName = cur.attributes().item(i).toAttr().name();
		
		if(!curNI.allowedAttributes.contains(attrName)) {
			qDebug() << "VALIDATIN ERR" << "TA" << attrName  << " in " << parentName;
			qDebug() << "note allowed attributes are:" << curNI.allowedAttributes;

			cur.attributes().removeNamedItem(attrName);
			i--;
		}
	}
				

	

    QDomNodeList children = cur.childNodes();
	
    for (int i = 0; i < children.size(); i++) {
        QDomNode node = children.at(i);
        //      qDebug() << i << "/" << children.size();
        if (node.isElement()) {
			//is subElement valid here?

			QString childName = node.toElement().tagName();
			
			if(!curNI.allowedTags.contains(childName)) {
				
				qDebug() << "VALIDATIN ERR" << "TS" << childName << " in " << parentName;
				qDebug() << "note allowed subElements are:" << curNI.allowedTags;
                
				cur.removeChild(node);
                i--;
            }
			else {
                dfs(node.toElement(), tabs);
			}
        }
        else if (node.isText()) {
            qDebug() << QString(tabs + 3, ' ') << node.toText().data();
        }
		else if (node.isComment()) {
            qDebug() << QString(tabs + 3, ' ') << "comment" << node.toComment().data();
        }
        else {
            throw 3.3;
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

	//attrs
    appendArrayToList(defaultAttributes, sizeof (defaultAttributes), textNI.allowedAttributes);

	textNI.canHaveText = true;
	textNI.canBeEmpty = true;


	for(int i=1; i< sizeof(textElements)/sizeof(QString); i++) {
		allowed[textElements[i]]=textNI;
	}



    qDebug() << structNI.allowedTags;
}


void MessageValidator::appendArrayToList(const QString *array, int arraySize, QStringList& list) {
    for (int i = 0; i < arraySize / sizeof (QString); i++) {
        list.append(array[i]);
    }
}


QString MessageValidator::validateMessage(QString message, bool* modified) {
    QDomDocument doc("document");

    QString errorMessage;
    int line, column;

    if (!doc.setContent(message, false, &errorMessage, &line, &column)) {
        qDebug() << errorMessage << " " << line << " " << column;
        exit(2);
    }

    dfs(doc.documentElement(), 0);
    qDebug() << doc.toString();
	return doc.toString();
}
