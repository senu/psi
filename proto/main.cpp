#include <QApplication>
#include <QPushButton>
#include <QWidget>

#include "htmlChatView.h"


int main(int argc, char *argv[]) {

	QApplication app(argc, argv);


	QWidget * frame = new QWidget();

	QPushButton nextMessageBtn("appendNextMessage", frame);
	QPushButton consMessageBtn("appendConsecutiveMessage", frame);

    HTMLChatView * view = new HTMLChatView(frame);

#warning change next line
    view->webView.load(QUrl("/home/senu/dev/psi/gsoc/repo/psi-fork/proto/themes/Satin.AdiumMessageStyle/Contents/Resources/tmp.html"));
	view->setGeometry(0,0,300,200);
    view->show();

	nextMessageBtn.setGeometry(0,800,50,20);
    nextMessageBtn.show();

	consMessageBtn.setGeometry(70,800,50,20);
    consMessageBtn.show();
	
	frame->setGeometry(0,0,800,900);
	frame->show();

    QObject::connect(&nextMessageBtn, SIGNAL(clicked()), view, SLOT(appendNextMessage()));
    QObject::connect(&consMessageBtn, SIGNAL(clicked()), view, SLOT(appendConsecutiveMessage()));

	int ret = app.exec();
	delete view;
	return ret;
}



