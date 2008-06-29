
#include <QtXml>

#include <QApplication>

#include "testForm.h"
#include "messageValidator.h"
#ifdef TESTS
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

#include "tests/testMessageValidator.h"
#endif
int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    int ret = 0;

#ifdef TESTS
	MessageValidator vaildator;
	
	CPPUNIT_TEST_SUITE_REGISTRATION (TestMessageValidator);

// informs test-listener about testresults
    CPPUNIT_NS :: TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS :: TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS :: BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS :: TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS :: TestFactoryRegistry :: getRegistry ().makeTest ());
    testrunner.run (testresult);

    // output results in compiler-format
    CPPUNIT_NS :: TextOutputter compileroutputter (&collectedresults, std::cerr);
    compileroutputter.write ();
#endif

    TestForm * form = new TestForm(0);
    form->show();
    ret = app.exec();
    delete form;
	/*
*/

    return ret;

}



