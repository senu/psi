#include <QPushButton>

#include "htmlchateditframe.h"


HTMLChatEditFrame::HTMLChatEditFrame(QWidget* parent) : QWidget(parent) {

    editor = new HTMLChatEdit(this);
	QPushButton * boldBtn = new QPushButton("bold", this);
	editor->setGeometry(0,30, 200, 80);
	
	this->setGeometry(0,0, 300, 300);

    this->show();
	
    QObject::connect(boldBtn, SIGNAL(clicked()), editor, SLOT(textBold()));
}

HTMLChatEditFrame::~HTMLChatEditFrame() {
	delete editor;
}
