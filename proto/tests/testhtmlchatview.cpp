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
    ce->setTimeStamp(QDateTime::currentDateTime());
    ce->setNick("senu");
    ce->setService("Jabber");
    ce->setConsecutive(true);
    ce->setLocal(true);
    ce->setUserIconPath("http://url.com");

    view->appendMessage(ce);


    //TODO add Kopete compatibility tests
    //TODO span 

    checkResultBody(
                    "<div><b style=\"color: green\">header</b></div><hr>"
                    "<div id=\"Chat\">"
                    "<div class=\"status_container\"><div>1970-02-05 - 01:00</div>"
                    "Finished downloading screen.png.<br></div>"
                    "<span><div class=\"combine\"><div class=\"ctime\">2008-07-03 - 11:41</div>"
                    "senu - Jabber - SENDER_JID - http://url.com :: message \" <b > "
					".</div><div id=\"insert\"></div></span>"
                    "</div>"
                    "<hr><div><b style=\"color: red\">footer</b></div>"
                    );
}


void TestHTMLChatView::clearMessages() {
	CPPUNIT_FAIL("test not written");
}


void TestHTMLChatView::tchemeChanged() {
	CPPUNIT_FAIL("test not written");
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
    QTest::qWait(1000); //TODO
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
    out = out.right(out.size() - a - 6);

    CPPUNIT_ASSERT_EQUAL(validOutput.toStdString(), out.toStdString());
}
