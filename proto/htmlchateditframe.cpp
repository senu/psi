#include <QPushButton>

#include "htmlchateditframe.h"


HTMLChatEditFrame::HTMLChatEditFrame(QWidget* parent, const QString& iconPath) : QWidget(parent) {

    QPushButton * linkBtn = new QPushButton("link", this);
    
    toolBar = new QToolBar(this);
    toolBar->setIconSize(QSize(16,16));

    linkBtn->move(450, 40);

    editor = new HTMLChatEdit(this, toolBar, iconPath);
    editor->setGeometry(0, 30, 400, 150);

    this->setGeometry(0, 0, 600, 400);
    this->show();

    QObject::connect(linkBtn, SIGNAL(clicked()), editor, SLOT(insertAnchor()));
    QObject::connect(linkBtn, SIGNAL(clicked()), editor, SLOT(insertImage()));
}


HTMLChatEditFrame::~HTMLChatEditFrame() {
    delete editor;
}

QString HTMLChatEditFrame::toHTML() {
    return editor->message();
}