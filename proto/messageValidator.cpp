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


void MessageValidator::dfs(QDomElement cur, int tabs) {
    tabs += 3;

	qDebug() << QString(tabs, ' ') << cur.tagName() << " ---> " << (bool)allowed.contains(cur.tagName());
		
	QDomNodeList children = cur.childNodes();
	for (int i = 0; i < children.size(); i++) {
		QDomNode node = children.at(i);
		qDebug() << i << "/" << children.size();
		if (node.isElement()){ 
			if (node.toElement().tagName() == "p") {
				cur.removeChild(node);
				i--;
			}
			else
				dfs(node.toElement(), tabs);
		}
		else if (node.isText()) {
			qDebug() << QString(tabs+3, ' ') << node.toText().data();
		}
		else {
			throw 3.3;
		}
	}


}

MessageValidator::MessageValidator() {
	arrayToList(textElements, sizeof(textElements));

    QDomDocument doc("document");

    QString message =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<div>senu tu byl"
            "<b>i jest fajny</b>"
			"joined text?"
            "<p>"
            "<i>kursywa</i>"
            "<table>NOWAY</table>"
			"<br/>"
			"a teraz cos zupelnie z innej beczki"
            "</p>"
			"a teraz cos zupelnie z innej beczki 444"
			"<b>xx</b>"
            "</div>";

    QString errorMessage;
    int line, column;

    if (!doc.setContent(message, false, &errorMessage, &line, &column)) {
        qDebug() << errorMessage << " " << line << " " << column;
        exit(2);
    }

    dfs(doc.documentElement(), 0);
}

MessageValidator::~MessageValidator() {

}

void MessageValidator::generateAllowedDict() {

}

QStringList MessageValidator::arrayToList(const QString *array, int arraySize) {
	QStringList list;
	
	for(int i=0; i < arraySize/sizeof(QString); i++) {
		list.append(array[i]);
	}
	
	return list;
}



