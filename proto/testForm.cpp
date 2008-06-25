#include <QPushButton>
#include <QWidget>

#include "testForm.h"
#include "htmlChatView.h"

/** Widget used for testing ChatView */
TestForm::TestForm(QWidget *parent) 
   : QFrame(parent)
{

	QPushButton * nextMessageBtn = new QPushButton("appendNextMessage", this);
	QPushButton * consMessageBtn = new QPushButton("appendConsecutiveMessage", this);
	QPushButton * eventMessageBtn = new QPushButton("appendEvent", this);

    HTMLChatView * view = new HTMLChatView(this);

#warning change next line
    view->webView.load(QUrl("/home/senu/dev/psi/gsoc/repo/psi-fork/proto/themes/Satin.AdiumMessageStyle/Contents/Resources/tmp.html"));
	view->setGeometry(0,0,300,200);
    view->show();

	nextMessageBtn->setGeometry(0,800,70,30);
    nextMessageBtn->show();

	consMessageBtn->setGeometry(90,800,70,30);
    consMessageBtn->show();

	eventMessageBtn->setGeometry(180,800,70,30);
    eventMessageBtn->show();

    messageEdit = new QLineEdit("message body", this);
    messageEdit->setGeometry(0,870,180,30);
	
	this->setGeometry(0,0,800,950);

    this->show();

    QObject::connect(nextMessageBtn, SIGNAL(clicked()), this, SLOT(onNextButtonClicked()));
    QObject::connect(consMessageBtn, SIGNAL(clicked()), this, SLOT(onConsecutiveButtonClicked()));
    QObject::connect(eventMessageBtn, SIGNAL(clicked()), this, SLOT(onEventButtonClicked()));

    QObject::connect(this, SIGNAL(messageCreated(const MessageChatEvent*)), view, SLOT(appendMessage(const MessageChatEvent*)));
    QObject::connect(this, SIGNAL(eventCreated(const ChatEvent*)), view, SLOT(appendEvent(const ChatEvent*)));

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


void TestForm::onEventButtonClicked() {

	FileTransferChatEvent *ev = new FileTransferChatEvent();

	emit eventCreated(ev);
}
