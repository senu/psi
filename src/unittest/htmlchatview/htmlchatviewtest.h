#ifndef _TESTHTMLCHATVIEW_H
#define	_TESTHTMLCHATVIEW_H

#include <QString>
#include <QFrame>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../htmlchatview.h"
#include "../../iconserver.h"


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
class HTMLChatViewTest : public CPPUNIT_NS::TestCase {

    CPPUNIT_TEST_SUITE(HTMLChatViewTest);
    CPPUNIT_TEST(onlyFooterAndHeader);
    CPPUNIT_TEST(messagesAndEvents);

    CPPUNIT_TEST(clearMessages);
    CPPUNIT_TEST(emoteEvent);
    CPPUNIT_TEST(themeChanged);
    
    CPPUNIT_TEST(keywordEscaping);
    CPPUNIT_TEST(javaScriptCSSValidatorIntegration);
    
    CPPUNIT_TEST(defaultIcons);

    CPPUNIT_TEST(noActionTemplate);
    CPPUNIT_TEST(noOutgoingTemplates);

    CPPUNIT_TEST_SUITE_END();

public:
    /** I know, I know. */
    void waitUntil(volatile  bool * flag);

protected:
    /** No changes in output message*/
    void onlyFooterAndHeader();
    void messagesAndEvents();

    void emoteEvent();

    void clearMessages();
    void themeChanged();

    void noActionTemplate();
    void noOutgoingTemplates();

	/** Checks if HTMLChatView uses JavaScript CSS Validator */
    void javaScriptCSSValidatorIntegration();

	/** Checks if HTMLChatView uses JavaScript CSS Validator */
    void defaultIcons();

    /** Keyword values with %% have to be escaped */
    void keywordEscaping();

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
