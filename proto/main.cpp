#include <QApplication>
#include <QPushButton>
#include <QWidget>

#include "htmlChatView.h"


int main(int argc, char *argv[]) {

	QApplication app(argc, argv);


	QWidget * frame = new QWidget();

	QPushButton hello("go", frame);

    HTMLChatView * view = new HTMLChatView(frame);

    view->webView.load(QUrl("file:///home/senu/cur/tmp.html"));
	view->setGeometry(0,0,300,200);
    view->show();

	hello.setGeometry(0,800,50,20);
    hello.show();
	frame->setGeometry(0,0,800,900);
	frame->show();

    QObject::connect(&hello, SIGNAL(clicked()), view, SLOT(evaluateJS()));

	return app.exec();
}



