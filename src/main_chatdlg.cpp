#include <QtXml>
#include <QApplication>

#include "testform.h"
#include "messagevalidator.h"

#ifdef TESTS
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

#include "tests/testhtmlchatview.h"
#include "tests/testMessageValidator.h"
#endif

// ./proto [tests]


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    int ret = 0;

    TestForm * form = new TestForm(0);
    form->show();
    ret = app.exec();
    delete form;

    return ret;
}



