#ifndef _TESTMESSAGEVALIDATOR_H
#define	_TESTMESSAGEVALIDATOR_H


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../messageValidator.h"
#include "testhtmlchatview.h"


/** CppUnit unit test for MessageValidator */
class TestMessageValidator : public CPPUNIT_NS::TestFixture {

    CPPUNIT_TEST_SUITE(TestMessageValidator);
    CPPUNIT_TEST(goodMessage);
    CPPUNIT_TEST(badTagWithChildrenMessage);
    CPPUNIT_TEST(badAttributeMessage);
    CPPUNIT_TEST(cannotHaveTextAttr);
    CPPUNIT_TEST(emptyMessage);
    CPPUNIT_TEST(scriptInCDATAMessage);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    //    void tearDown(void);

protected:
    /** No changes in output message*/
    void goodMessage();
    void badTagWithChildrenMessage();
    void badAttributeMessage();
    void cannotHaveTextAttr();
    void emptyMessage();
    void scriptInCDATAMessage();

    void genericTest(QString inMessage, QString validMessage);

    MessageValidator val;
};


#endif	

