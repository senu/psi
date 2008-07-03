#include <QtTest>
#include <qt4/QtCore/qdatetime.h>
#include <QString>

#include "testhtmlchatview.h"


#include "config.h"


void TestHTMLChatView::setUp() {
    //    view = NULL;
}


void TestHTMLChatView::onlyFooterAndHeader() {
    prepareTest("testingTheme/");
    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\"></div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void TestHTMLChatView::messagesAndEvents() {
    prepareTest("testingTheme/");

    appendSomeEvents();

    //TODO add Kopete compatibility tests
    //TODO span 

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"
                    "<div class=\"status_container\"><div>1970-02-05 - 01:00</div>"
                    "Finished downloading screen.png.<br></div>"
                    "<span><div class=\"combine\"><div class=\"ctime\">1970-02-05 - 01:00</div>"
                    "senu - Jabber - senu@jabber.pl - http://url.com :: message \" <br> "
                    ".</div><div id=\"insert\"></div></span>"
                    "</div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void TestHTMLChatView::clearMessages() {
    prepareTest("testingTheme/");
    appendSomeEvents();
    view->clear();

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"
                    "</div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void TestHTMLChatView::tchemeChanged() {
    prepareTest("testingTheme/");

    appendSomeEvents();

    QTest::qWait(1200); //TODO
    theme.readTheme(_THEMEPATH"themes/testingTheme2/");
    view->setTheme(theme);
    QTest::qWait(1200); //TODO

    checkResultBody(
                    "<div><b style=\"color: green\">header2</b></div><hr>"
                    "<div id=\"Chat\">"
                    "<div class=\"status_container\"><div>1970-02-05 -- 01:00</div>"
                    "Finished downloading screen.png.<br></div>"
                    "<span><div class=\"combine\"><div class=\"ctime\">1970-02-05 -- 01:00</div>"
                    "senu - Jabber - senu@jabber.pl - http://url.com :: message \" <br> "
                    ".</div><div id=\"insert\"></div></span>"
                    "</div>"
                    "<hr><div><b style=\"color: red\">footer2</b></div>"
                    );
}


void TestHTMLChatView::noActionTemplate() {
    CPPUNIT_FAIL("test not written");
}


void TestHTMLChatView::noOutgoingTemplates() {
    CPPUNIT_FAIL("test not written");
}


void TestHTMLChatView::prepareTest(QString themePath) {
    form = new QFrame(0);

    theme.readTheme(_THEMEPATH + QString("themes/") + themePath);
    view = new HTMLChatView(form, theme);
    view->init();
    QTest::qWait(1200); //TODO
}


void TestHTMLChatView::checkResultBody(QString validOutput) {
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


void TestHTMLChatView::appendSomeEvents() {
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

    view->appendMessage(ce);
}