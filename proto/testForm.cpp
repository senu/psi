#include <QPushButton>
#include <QWidget>

#include "testForm.h"
#include "htmlChatView.h"

TestForm::TestForm(QWidget *parent) 
   : QFrame(parent)
{

	QPushButton * nextMessageBtn = new QPushButton("appendNextMessage", this);
	QPushButton * consMessageBtn = new QPushButton("appendConsecutiveMessage", this);

    HTMLChatView * view = new HTMLChatView(this);

#warning change next line
    view->webView.load(QUrl("/home/senu/dev/psi/gsoc/repo/psi-fork/proto/themes/Satin.AdiumMessageStyle/Contents/Resources/tmp.html"));
	view->setGeometry(0,0,300,200);
    view->show();

	nextMessageBtn->setGeometry(0,800,50,20);
    nextMessageBtn->show();

	consMessageBtn->setGeometry(70,800,50,20);
    consMessageBtn->show();

    messageEdit = new QLineEdit("message body", this);
    messageEdit->setGeometry(0,870,180,30);
	
	this->setGeometry(0,0,800,950);

    this->show();

    QObject::connect(nextMessageBtn, SIGNAL(clicked()), this, SLOT(onNextButtonClicked()));
    QObject::connect(consMessageBtn, SIGNAL(clicked()), this, SLOT(onConsecutiveButtonClicked()));

    QObject::connect(this, SIGNAL(messageCreated(const MessageChatEvent*)), view, SLOT(appendMessage(const MessageChatEvent*)));

}


void TestForm::onConsecutiveButtonClicked() {
    MessageChatEvent * ce = new MessageChatEvent();
    ce->setBody(messageEdit->text());
    ce->setTimestamp(QDateTime::currentDateTime());
    ce->setNick("senu");
    ce->setConsecutive(true);
         
    emit messageCreated(ce);
}

void TestForm::onNextButtonClicked() { // copy-paste :D
    MessageChatEvent * ce = new MessageChatEvent();
    ce->setBody(messageEdit->text());
    ce->setTimestamp(QDateTime::currentDateTime());
    ce->setNick("Pawel Wiejacha");
    ce->setConsecutive(false);

    emit messageCreated(ce);
}
