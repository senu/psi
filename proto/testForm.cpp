#include <QPushButton>
#include <QWidget>

#include "testForm.h"
#include "htmlChatView.h"

TestForm::~TestForm() {
	delete view;
}

/** Widget used for testing ChatView */
TestForm::TestForm(QWidget *parent) 
   : QFrame(parent)
{

	QPushButton * nextMessageBtn = new QPushButton("appendNextMessage", this);
	QPushButton * consMessageBtn = new QPushButton("appendConsecutiveMessage", this);
	QPushButton * eventMessageBtn = new QPushButton("appendEvent", this);
	QPushButton * loadThemeBtn = new QPushButton("load theme", this);

	comboBox = new QComboBox(this);

	nextMessageBtn->setGeometry(0,800,100,30);
    nextMessageBtn->show();

	consMessageBtn->setGeometry(110,800,100,30);
    consMessageBtn->show();

	eventMessageBtn->setGeometry(220,800,100,30);
    eventMessageBtn->show();
	
	loadThemeBtn->setGeometry(330,800,140,30);
    loadThemeBtn->show();

    messageEdit = new QLineEdit("message body", this);
    messageEdit->setGeometry(0,870,180,30);


	themeList.readThemes();

	QString themePath;
	QStringList themeNames = themeList.themeNames();

	foreach(themePath, themeNames) {
		qDebug() << themePath << themeList.themePath(themePath);
	}

	
	comboBox->addItems(themeNames);
    comboBox->setGeometry(0,700,180,40);
	comboBox->show();

	this->setGeometry(0,0,800,950);

    this->show();
	
    QObject::connect(nextMessageBtn, SIGNAL(clicked()), this, SLOT(onNextButtonClicked()));
    QObject::connect(consMessageBtn, SIGNAL(clicked()), this, SLOT(onConsecutiveButtonClicked()));
    QObject::connect(eventMessageBtn, SIGNAL(clicked()), this, SLOT(onEventButtonClicked()));
    QObject::connect(loadThemeBtn, SIGNAL(clicked()), this, SLOT(onLoadTheme()));
}


void TestForm::onConsecutiveButtonClicked() {
	MessageChatEvent * ce = new MessageChatEvent();
	
	bool modified;
	ce->setBody(msgVal.validateMessage("<msg>"+messageEdit->text()+"</msg>", &modified));
    
	ce->setTimestamp(QDateTime::currentDateTime());
    ce->setNick("senu");
    ce->setService("Jabber");
    ce->setConsecutive(true);
	ce->setLocal(true);
         
    emit messageCreated(ce);
}

void TestForm::onNextButtonClicked() { // copy-paste :D
    MessageChatEvent * ce = new MessageChatEvent();
    
	bool modified;
	ce->setBody(msgVal.validateMessage("<body>"+messageEdit->text()+"</body>", &modified));
	
    ce->setTimestamp(QDateTime::currentDateTime());
    ce->setConsecutive(false);
    ce->setService("Jabber");
	ce->setLocal(qrand()%2);
	if(ce->isLocal())
	    ce->setNick("Pawel Wiejacha");
	else
	    ce->setNick("Kot behemot");

    emit messageCreated(ce);
}


void TestForm::onEventButtonClicked() {

	FileTransferChatEvent *ev = new FileTransferChatEvent();

	emit eventCreated(ev);

	StatusChatEvent *ev2 = new StatusChatEvent();

	ev2->setStatusMessage("status message zzz");

	emit eventCreated(ev2);
}

void TestForm::onLoadTheme() {
	
	QString themeName = comboBox->currentText();
	HTMLChatTheme theme = themeList.themePath(themeName);
	
    view = new HTMLChatView(this, theme);
	view->init();
	view->setGeometry(0,0,300,200);
    view->show();

    QObject::connect(this, SIGNAL(messageCreated(const MessageChatEvent*)), view, SLOT(appendMessage(const MessageChatEvent*)));
    QObject::connect(this, SIGNAL(eventCreated(const ChatEvent*)), view, SLOT(appendEvent(const ChatEvent*)));
}
