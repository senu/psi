#include <QPushButton>
#include <QWidget>
#include <QUrl>
#include <QFileDialog>
#include <QDir>

#include "testform.h"
#include "htmlchatview.h"
#include "filelransferchatevent.h"
#include "htmlchatview.h"

#include "htmlchateditframe.h"
#include "nullhtmltextformatter.h"


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
    QPushButton * runTestsBtn = new QPushButton("css tests", this);

    themeComboBox = new QComboBox(this);
    variantComboBox = new QComboBox(this);

    nextMessageBtn->setGeometry(0, 650, 100, 30);
    nextMessageBtn->show();

    consMessageBtn->setGeometry(110, 650, 100, 30);
    consMessageBtn->show();

    eventMessageBtn->setGeometry(220, 650, 100, 30);
    eventMessageBtn->show();

    loadThemeBtn->setGeometry(330, 650, 140, 30);
    loadThemeBtn->show();

    variantThemeBtn->setGeometry(480, 650, 140, 30);
    clearBtn->setGeometry(640, 650, 140, 30);
    runTestsBtn->setGeometry(800, 650, 140, 30);

    QString path = "/home/senu/dev/psi/gsoc/repo/psi-fork/src/";
    while (!QDir(path).isReadable()) {
        QFileDialog dialog(this, "Choose the theme parent folder", path);
        dialog.setFileMode(QFileDialog::DirectoryOnly);
        dialog.exec();
        path = dialog.directory().canonicalPath();
        qDebug() << "User chose folder " << path << " for themes.";
    }

    themePathEdit = new QLineEdit(path, this);
    themePathEdit->setGeometry(500, 700, 180, 30);

    themeList.readThemes(themePathEdit->text());

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

    frame = new HTMLChatEditFrame(this, themePathEdit->text() + "/icons/");
    frame->move(0, 750);


    this->setGeometry(0, 0, 920, 950);

    this->show();

    connect(nextMessageBtn, SIGNAL(clicked()), this, SLOT(onNextButtonClicked()));
    connect(consMessageBtn, SIGNAL(clicked()), this, SLOT(onConsecutiveButtonClicked()));
    connect(eventMessageBtn, SIGNAL(clicked()), this, SLOT(onEventButtonClicked()));
    connect(loadThemeBtn, SIGNAL(clicked()), this, SLOT(onLoadTheme()));
    connect(variantThemeBtn, SIGNAL(clicked()), this, SLOT(onLoadVariant()));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(onClear()));

    connect(runTestsBtn, SIGNAL(clicked()), this, SLOT(onRunTests()));
}


void TestForm::onConsecutiveButtonClicked() {
    MessageChatEvent * ce = new MessageChatEvent();

    bool modified;
    HTMLTextFormatter* formatter = new NullHTMLTextFormatter();
    ce->setBody(msgVal.validateMessage(frame->toHTML(), &modified, formatter));
    delete formatter;

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

    HTMLTextFormatter* formatter = new NullHTMLTextFormatter();
    ce->setBody(msgVal.validateMessage(frame->toHTML(), &modified, formatter));
    delete formatter;

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
        view = new HTMLChatView(this, *theme, themePathEdit->text());
        view->init();
        view->setGeometry(0, 0, 600, 600);
        view->show();

        connect(this, SIGNAL(messageCreated(const MessageChatEvent*)), view, SLOT(appendMessage(const MessageChatEvent*)));
        connect(this, SIGNAL(eventCreated(const ChatEvent*)), view, SLOT(appendEvent(const ChatEvent*)));
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
    testsView->load(QUrl(themePathEdit->text() + "/tests/testRunner.html")); //TODO
}
