#include <QtTest>
#include <QDateTime>
#include <QString>
#include <QFrame>

#include "htmlchatviewtest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(HTMLChatViewTest);

void HTMLChatViewTest::onlyFooterAndHeader() {
    prepareTest("testingTheme/");
    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\"></div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void HTMLChatViewTest::messagesAndEvents() {
    prepareTest("testingTheme/");

    appendSomeEvents();

    qDebug() << "after app ft event";
    waitUntil(&helper.append);

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"

                    "<div class=\"status_container\"><div>fileTransferComplete :: 1970-02-05 - 01:00</div>"
                    "Finished downloading screen.png. || event fileTransfer <br></div><span>"
                    "<div class=\"combine\"><div class=\"ctime\">1970-02-05 - 01:00</div>"
                    "http://url.com - myicon.png - ltr - senu@jabber.pl - senu - "
                    "Jabber - senu@jabber.pl - http://url.com :: message \" <br>"
                    " . || message outgoing <span style=\"color: #194978\">COLOR</span>"
                    "</div><div id=\"insert\"></div></span>"

                    "</div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void HTMLChatViewTest::clearMessages() {
    prepareTest("testingTheme/");
    appendSomeEvents();

    waitUntil(&(helper.append));
    view->clear();

    QTest::qWait(200);

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"
                    "</div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void HTMLChatViewTest::themeChanged() {
    prepareTest("testingTheme/");

    appendSomeEvents();

    waitUntil(&(helper.append));

    theme.readTheme(QDir::currentPath() + "/themes/testingTheme2/");

    helper.init = false;
    view->setTheme(theme);

    waitUntil(&(helper.init));

    checkResultBody(
                    "<div><b style=\"color: green\">header2</b></div><hr>"
                    "<div id=\"Chat\">"

                    "<div class=\"status_container\"><div>fileTransferComplete :: 1970-02-05 -- 01:00</div>"
                    "Finished downloading screen.png. || event fileTransfer<br></div>"

                    "<span><div class=\"combine\"><div class=\"ctime\">1970-02-05 -- 01:00</div>"
                    "senu - Jabber - senu@jabber.pl - http://url.com :: message \" <br> "
                    ".</div><div id=\"insert\"></div></span>"
                    "</div>"
                    "<hr><div><b style=\"color: red\">footer2</b></div>"
                    );
}


void HTMLChatViewTest::noActionTemplate() {
    prepareTest("testingTheme_noAction/");

    QDateTime time;
    time.setTime_t(24 * 60 * 60 * 35);

    EmoteChatEvent * event = new EmoteChatEvent();
    event->setLocal(false);
    event->setMessage("is working hard");
    event->setNick("Pawel Wiejacha");
    event->setService("Jabber");
    event->setJid("senu@jabber.pl");
    event->setUserIconPath("http://userserve-ak.last.fm/serve/50/4272669.jpg");
    event->setTimeStamp(time);

    view->appendEvent(event);
    waitUntil(&(helper.append));

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"


                    "<div class=\"status_container\"><div>emote :: 1970-02-05 - 01:00</div>"
                    "Pawel Wiejacha is working hard || event emote <br></div>"
                    "<div id=\"insert\"></div>"

                    "</div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void HTMLChatViewTest::noOutgoingTemplates() {
    prepareTest("testingTheme_noOutgoing/");

    QDateTime time;
    time.setTime_t(24 * 60 * 60 * 35);
    MessageChatEvent * ce = new MessageChatEvent();

    ce->setBody("message \" <br/> .");
    ce->setTimeStamp(time);
    ce->setNick("senu");
    ce->setService("Jabber");
    ce->setConsecutive(false);
    ce->setJid("senu@jabber.pl");
    ce->setLocal(true);
    ce->setUserIconPath("http://url.com");
    ce->setUserStatusIcon("myicon.png");

    view->appendMessage(ce);
    waitUntil(&(helper.append));

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"

                    "<div class=\"combine\"><div class=\"ctime\">1970-02-05 - 01:00</div>senu - message \" "
                    "<br> . || message outgoing</div><div id=\"insert\"></div>"

                    "</div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void HTMLChatViewTest::emoteEvent() {
    prepareTest("testingTheme/");

    QDateTime time;
    time.setTime_t(24 * 60 * 60 * 35);

    EmoteChatEvent * event = new EmoteChatEvent();
    event->setLocal(false);
    event->setMessage("is working hard");
    event->setNick("Pawel Wiejacha");
    event->setService("Jabber");
    event->setJid("senu@jabber.pl");
    event->setUserIconPath("http://userserve-ak.last.fm/serve/50/4272669.jpg");
    event->setUserStatusIcon("myicon.png");
    event->setUserColor("#123456");
    event->setTimeStamp(time);

    view->appendEvent(event);
    waitUntil(&(helper.append));

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"

                    "<div class=\"status_container\"><div>1970-02-05 - 01:00</div>"
                    "Pawel Wiejacha is working hard<br> "
                    "#123456 - myicon.png - ltr - senu@jabber.pl - Jabber - senu@jabbe"
                    "r.pl - http://userserve-ak.last.fm/serve/50/4272669.jpg - 01:00 || event emote</div>"
                    "<div id=\"insert\"></div>"


                    "</div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void HTMLChatViewTest::javaScriptCSSValidatorIntegration() {
    prepareTest("testingTheme/");

    QDateTime time;
    time.setTime_t(24 * 60 * 60 * 35);

    MessageChatEvent * ce = new MessageChatEvent();

    ce->setBody("message \" <div style=\"border-color: red; color: green \"></div> \\ <br/> .");

    ce->setTimeStamp(time);
    ce->setNick("senu");
    ce->setService("Jabber");
    ce->setConsecutive(false);
    ce->setJid("senu@jabber.pl");
    ce->setLocal(true);
    ce->setUserIconPath("http://url.com");
    ce->setUserStatusIcon("myicon.png");
    ce->setUserColor("#123456");

    view->appendMessage(ce);

    waitUntil(&helper.append);

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"

                    "<div class=\"combine\"><div class=\"ctime\">1970-02-05 - 01:00</div>"
                    "http://url.com - myicon.png - ltr - senu@jabber.pl - senu - "
                    "Jabber - senu@jabber.pl - http://url.com :: "

                    "message \" <div style=\"color:green;\"></div> \\ <br> . " //

                    "|| message outgoing <span style=\"color: #194978\">COLOR</span>"
                    "</div>"

                    "<div id=\"insert\"></div>"

                    "</div>"
                    "<hr>"
                    "<div><b style=\"color: red\">footer</b></div>"
                    );
}


void HTMLChatViewTest::defaultIcons() {
    prepareTest("testingTheme/");

    QDateTime time;
    time.setTime_t(24 * 60 * 60 * 35);

    MessageChatEvent * ce = new MessageChatEvent();

    ce->setBody("message");

    ce->setTimeStamp(time);
    ce->setNick("senu");
    ce->setService("Jabber");
    ce->setConsecutive(false);
    ce->setJid("senu@jabber.pl");
    ce->setLocal(true);
    ce->setUserIconPath("outgoing"); //
    ce->setUserStatusIcon("myicon.png");
    ce->setUserColor("#123456");

    view->appendMessage(ce);

    waitUntil(&helper.append);

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"

                    "<div class=\"combine\"><div class=\"ctime\">1970-02-05 - 01:00</div>"
                    "Outgoing/buddy_icon.png - myicon.png - ltr - senu@jabber.pl - senu - " //
                    "Jabber - senu@jabber.pl - Outgoing/buddy_icon.png :: " //

                    "message"

                    " || message outgoing <span style=\"color: #194978\">COLOR</span>"
                    "</div>"

                    "<div id=\"insert\"></div>"

                    "</div>"
                    "<hr>"
                    "<div><b style=\"color: red\">footer</b></div>"
                    );

}


void HTMLChatViewTest::prepareTest(QString themePath) {

    QApplication app();

    form = new QFrame(0);

    helper.append = false;
    helper.init = false;

    theme.readTheme(QDir::currentPath() + QString("/themes/") + themePath);
    view = new HTMLChatView(form, theme, new IconServer());

    QObject::connect(view, SIGNAL(appendFinished()), &helper, SLOT(onAppendFinished()));
    QObject::connect(view, SIGNAL(initDocumentFinished()), &helper, SLOT(onInitDocumentFinished()));

    view->init();
    waitUntil(&(helper.init));
}


void HTMLChatViewTest::checkResultBody(QString validOutput) {
    QString out = view->dumpContent();

    delete view;
    delete form;

    int a = out.indexOf("<body>"),
        b = out.lastIndexOf("</body>");

    if (a < 0 || b < 0) {
        CPPUNIT_FAIL("no <body> element");
    }

    out.chop(out.size() - b);
    out = out.right(out.size() - a - 6).replace('\n', "");
    validOutput.replace('\n', "");

    for (int i = 0; i < validOutput.size(); ++i) {
        if (validOutput[i] != out[i]) {
            qDebug() << i << out.left(i);
            break;
        }
    }


    CPPUNIT_ASSERT_EQUAL(validOutput.toStdString(), out.toStdString());
}


void HTMLChatViewTest::appendSomeEvents() {
    // FT event
    FileTransferChatEvent *event = new FileTransferChatEvent();
    QDateTime time;

    event->setFileName("screen.png");
    event->type = FileTransferChatEvent::Finished;
    time.setTime_t(24 * 60 * 60 * 35);
    event->setTimeStamp(time);

    view->appendEvent(event);

    // CM event
    MessageChatEvent * ce = new MessageChatEvent();

    ce->setBody("message \" <br/> .");
    ce->setTimeStamp(time);
    ce->setNick("senu");
    ce->setService("Jabber");
    ce->setConsecutive(true);
    ce->setJid("senu@jabber.pl");
    ce->setLocal(true);
    ce->setUserIconPath("http://url.com");
    ce->setUserStatusIcon("myicon.png");
    ce->setUserColor("#123456");

    view->appendMessage(ce);
}


void CppUnitHelper::onAppendFinished() {
    qDebug() << "on append finished";
    append = true;
}


void CppUnitHelper::onInitDocumentFinished() {
    qDebug() << "on init finished";
    init = true;
}


void HTMLChatViewTest::waitUntil(volatile bool * flag) {
    while (! *flag) {
        qDebug() << "waiting";
        QTest::qWait(50);
    }
}
