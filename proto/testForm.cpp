#include <QPushButton>
#include <QWidget>
#include <QUrl>

#include "testForm.h"
#include "htmlChatView.h"
#include "fileTransferChatEvent.h"
#include "htmlChatView.h"

#include "config.h"
#include "htmlchateditframe.h"


TestForm::~TestForm() {
    delete view;
    delete theme;
}


/** Widget used for testing ChatView */
TestForm::TestForm(QWidget *parent)
: QFrame(parent) {

    view = 0;
    theme = 0;

    QPushButton * nextMessageBtn = new QPushButton("appendNextMessage", this);
    QPushButton * consMessageBtn = new QPushButton("appendConsecutiveMessage", this);
    QPushButton * eventMessageBtn = new QPushButton("appendEvent", this);
    QPushButton * loadThemeBtn = new QPushButton("load theme", this);
    QPushButton * variantThemeBtn = new QPushButton("load variant", this);
    QPushButton * clearBtn = new QPushButton("clear messages", this);
    QPushButton * runTestsBtn = new QPushButton("run tests", this);

    themeComboBox = new QComboBox(this);
    variantComboBox = new QComboBox(this);

    nextMessageBtn->setGeometry(0, 800, 100, 30);
    nextMessageBtn->show();

    consMessageBtn->setGeometry(110, 800, 100, 30);
    consMessageBtn->show();

    eventMessageBtn->setGeometry(220, 800, 100, 30);
    eventMessageBtn->show();

    loadThemeBtn->setGeometry(330, 800, 140, 30);
    loadThemeBtn->show();

    variantThemeBtn->setGeometry(480, 800, 140, 30);
    clearBtn->setGeometry(640, 800, 140, 30);
    runTestsBtn->setGeometry(800, 800, 140, 30);

    messageEdit = new QLineEdit("message body", this);
    messageEdit->setGeometry(0, 880, 180, 30);


    themeList.readThemes();

    QString themePath;
    QStringList themeNames = themeList.themeNames();


    foreach(themePath, themeNames) {
        qDebug() << themePath << themeList.themePath(themePath);
    }


    themeComboBox->addItems(themeNames);
    themeComboBox->setGeometry(0, 700, 180, 40);
    themeComboBox->show();

    variantComboBox->setGeometry(200, 700, 180, 40);
    variantComboBox->show();


	HTMLChatEditFrame * frame = new HTMLChatEditFrame(this);
	frame->show();

	
    this->setGeometry(0, 0, 920, 950);

    this->show();

    QObject::connect(nextMessageBtn, SIGNAL(clicked()), this, SLOT(onNextButtonClicked()));
    QObject::connect(consMessageBtn, SIGNAL(clicked()), this, SLOT(onConsecutiveButtonClicked()));
    QObject::connect(eventMessageBtn, SIGNAL(clicked()), this, SLOT(onEventButtonClicked()));
    QObject::connect(loadThemeBtn, SIGNAL(clicked()), this, SLOT(onLoadTheme()));
    QObject::connect(variantThemeBtn, SIGNAL(clicked()), this, SLOT(onLoadVariant()));
    QObject::connect(clearBtn, SIGNAL(clicked()), this, SLOT(onClear()));

    QObject::connect(runTestsBtn, SIGNAL(clicked()), this, SLOT(onRunTests()));
}


void TestForm::onConsecutiveButtonClicked() {
    MessageChatEvent * ce = new MessageChatEvent();

    bool modified;
    ce->setBody(msgVal.validateMessage("<msg>" + messageEdit->text() + "</msg>", &modified));

    ce->setTimeStamp(QDateTime::currentDateTime());
    ce->setNick("Pawel Wiejacha");
    ce->setJid("senu@jabber.pl");
    ce->setService("Jabber");
    ce->setConsecutive(true);
    ce->setLocal(true);

    ce->setUserIconPath("http://a.wordpress.com/avatar/liberumveto-48.jpg");

    emit messageCreated(ce);
}


void TestForm::onNextButtonClicked() { // copy-paste :D
    MessageChatEvent * ce = new MessageChatEvent();

    bool modified;
    ce->setBody(msgVal.validateMessage("<body>" + messageEdit->text() + "</body>", &modified));

    ce->setTimeStamp(QDateTime::currentDateTime());
    ce->setConsecutive(false);
    ce->setService("Jabber");
    ce->setLocal(qrand() % 2);
    if (ce->isLocal()) {
        ce->setNick("Pawel Wiejacha");
        ce->setJid("senu@jabber.pl");
        ce->setUserIconPath("http://userserve-ak.last.fm/serve/50/4272669.jpg");
    }
    else {
        ce->setNick("Kot Behemot");
        ce->setJid("behemot@jabber.ru");
        ce->setUserIconPath("http://a.wordpress.com/avatar/liberumveto-48.jpg");
    }


    emit messageCreated(ce);
}


void TestForm::onEventButtonClicked() {

    FileTransferChatEvent *ev = new FileTransferChatEvent();
    ev->setTimeStamp(QDateTime::currentDateTime());
    ev->type = FileTransferChatEvent::Aborted;
    ev->setFileName("screen.jpg");

    emit eventCreated(ev);

    StatusChatEvent *ev2 = new StatusChatEvent();

    ev2->setTimeStamp(QDateTime::currentDateTime());
    ev2->type = StatusChatEvent::Xa;
    ev2->setStatusMessage("status message zzz");

    emit eventCreated(ev2);

    EmoteChatEvent * ev3 = new EmoteChatEvent();
    ev3->setLocal(false);
    ev3->setMessage("is working hard");
    ev3->setNick("Pawel Wiejacha");
    ev3->setService("Jabber");
    ev3->setJid("senu@jabber.pl");
    ev3->setUserIconPath("http://userserve-ak.last.fm/serve/50/4272669.jpg");
    ev3->setTimeStamp(QDateTime::currentDateTime());

    emit eventCreated(ev3);

}


void TestForm::onLoadTheme() {

    QString themeName = themeComboBox->currentText();

    delete theme;
    theme = new HTMLChatTheme(themeList.themePath(themeName));

    variantComboBox->clear();
    variantComboBox->addItems(theme->variants());
}


void TestForm::onLoadVariant() {

    theme->setCurrentVariant(variantComboBox->currentText());

    if (view == NULL) {
        view = new HTMLChatView(this, *theme);
        view->init();
        view->setGeometry(0, 0, 300, 200);
        view->show();

        QObject::connect(this, SIGNAL(messageCreated(const MessageChatEvent*)), view, SLOT(appendMessage(const MessageChatEvent*)));
        QObject::connect(this, SIGNAL(eventCreated(const ChatEvent*)), view, SLOT(appendEvent(const ChatEvent*)));
    }
    else {
        view->setTheme(*theme);
    }
}


void TestForm::onClear() {
    view->clear();
}


void TestForm::onRunTests() {
	QWebView * testsView = new QWebView(0);
	testsView->show();
	testsView->load(QUrl(_THEMEPATH"/tests/testRunner.html")); //TODO
}
