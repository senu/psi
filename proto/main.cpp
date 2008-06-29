
#include <qt4/QtXml/qdom.h>

#include <QApplication>

#include "testForm.h"
#include "messageValidator.h"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    int ret = 0;


    TestForm * form = new TestForm(0);
    form->show();

	MessageValidator vaildator;

    ret = app.exec();
    delete form;


    return ret;

}



