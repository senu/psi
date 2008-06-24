#include <QApplication>

#include "testForm.h"


int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

    TestForm * form = new TestForm(0);
    form->show();



	int ret = app.exec();
//	delete view;
	return ret;
}



