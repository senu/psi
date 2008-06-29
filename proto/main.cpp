
#include <qt4/QtXml/qdom.h>

#include <QApplication>
#include <QtDebug>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QPair>

#include "testForm.h"


//TODO stack instead of recursion?
//TODO i assume (I didn't check) there's no copy passing non-reference QDomElement

//OK -> textNode, node we want to delete, textNode2 --delete--> != textNode + textNode2 

QStringList allowed;

/** per-Node structure used in XHTML-IM validation */
struct NodeInfo {
	
	/** Allowed direct child elements*/
	QStringList allowedTags;
	
	/** Allowed tag attributes */
	QStringList allowedAttributes;
	
	/** Can have textNode - eg. false for <br> */
	bool canHaveText; 

	bool canBeEmpty;//TODO i need to check xhtml rfc. Do we need that?
}; 

enum ValidationResult {
	OK,
	Modified,
	Removed
};


typedef QPair<ValidationResult, QDomNode> ValidatedNode;


void dfs(QDomElement cur, int tabs) {
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

QString tmp[]  = { "p", "b", "div"};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	for(int i = 0; i< sizeof(tmp)/sizeof(QString); i++)
		allowed.append(tmp[i]);

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


    int ret = 0;

	
   TestForm * form = new TestForm(0);
   form->show();



    ret = app.exec();
    delete form;
	 
     
    return ret;

}



