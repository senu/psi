#include <QPushButton>

#include "htmlchateditframe.h"


HTMLChatEditFrame::HTMLChatEditFrame(QWidget* parent) : QWidget(parent) {

    QPushButton * boldBtn = new QPushButton("bold", this);
    
    toolBar = new QToolBar(this);

    boldBtn->move(0, 40);

    editor = new HTMLChatEdit(this, toolBar);
    editor->setGeometry(0, 90, 200, 100);

    this->setGeometry(0, 0, 400, 400);
    this->show();

    QObject::connect(boldBtn, SIGNAL(clicked()), editor, SLOT(textBold()));
}


HTMLChatEditFrame::~HTMLChatEditFrame() {
    delete editor;
}
