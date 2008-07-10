#ifndef _TESTHTMLCHATVIEW_H
#define	_TESTHTMLCHATVIEW_H

#include <QString>
#include <QFrame>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../htmlChatView.h"


/** We cannot inherit from TestCase AND QObject */
class CppUnitHelper : public QObject {

Q_OBJECT
    public
slots:
    void onAppendFinished();
    void onInitDocumentFinished();

public:
    bool append;
    bool init;
};


/** CppUnit unit test for HTMLChatView */
class TestHTMLChatView : public CPPUNIT_NS::TestCase {

    CPPUNIT_TEST_SUITE(TestHTMLChatView);
    CPPUNIT_TEST(onlyFooterAndHeader);
    CPPUNIT_TEST(messagesAndEvents);

    CPPUNIT_TEST(clearMessages);
    CPPUNIT_TEST(emoteEvent);
    CPPUNIT_TEST(themeChanged);

    CPPUNIT_TEST(noActionTemplate);
    CPPUNIT_TEST(noOutgoingTemplates);

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);

    /** :/ */
    void waitUntil(volatile  bool * flag);
    //    void tearDown(void);

protected:
    /** No changes in output message*/
    void onlyFooterAndHeader();
    void messagesAndEvents();

    void emoteEvent();

    void clearMessages();
    void themeChanged();

    void noActionTemplate();
    void noOutgoingTemplates();

    void prepareTest(QString themePath);

    /** We check only \body contents; Deletes form and view */
    void checkResultBody(QString validOutput);

    /** Appends a couple of messages and events to view */
    void appendSomeEvents();

    HTMLChatView * view;
    HTMLChatTheme theme;
    QFrame * form;

    CppUnitHelper helper;
};



#endif

