
#include <qt4/QtGui/qtextedit.h>

#include <QTextCursor>
#include <QUrl>
#include <QImage>
#include <QtDebug>
#include <QActionGroup>
#include <qt4/QtCore/qnamespace.h>
#include <qt4/Qt/qglobal.h>
#include <qt4/QtCore/qnamespace.h>
#include <qt4/QtCore/qnamespace.h>

#include "htmlchatedit.h"
#include "config.h"


HTMLChatEdit::HTMLChatEdit(QWidget* parent, QToolBar * _toolBar) : QTextEdit(parent) {

    toolBar = _toolBar;
    iconPath = QString(_THEMEPATH) + "/icons/";

    initActions();

	setText("Lorem ipsum costam costam i jeszcze cos tam costam.");
	
    show();
}


void HTMLChatEdit::textBold() {
    QTextCharFormat format;
    format.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);

    mergeFormat(format);

}


void HTMLChatEdit::textItalic() {
    QTextCharFormat format;
    format.setFontItalic(actionTextItalic->isChecked());

    mergeFormat(format);
}


void HTMLChatEdit::textUnderline() {
    QTextCharFormat format;
    format.setFontUnderline(actionTextUnderline->isChecked());

    mergeFormat(format);
}


void HTMLChatEdit::textAlign(QAction* alignAction) {
    setAlignment((Qt::Alignment)alignAction->property("align").toInt());
}


void HTMLChatEdit::fontFamily(const QString& fontName) {
}


void HTMLChatEdit::fontSize(const QString& size) {
}


void HTMLChatEdit::textColor() {
}


void HTMLChatEdit::textBackground() {
}


void HTMLChatEdit::insertImage(QString url) { //TODO

    QTextCursor cursor = textCursor();
    QImage img = QImage("/usr/share/icons/oxygen/128x128/apps/kmail.png");
    document()->addResource(QTextDocument::ImageResource, QUrl("myimage"), img);

    cursor.insertImage("myimage");
}


void HTMLChatEdit::insertAnchor(QString url, QString name) {
}


void HTMLChatEdit::cursorPosChanged() {
}


void HTMLChatEdit::mergeFormat(const QTextCharFormat& format) {
    QTextCursor cursor = textCursor();

    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }

    cursor.mergeCharFormat(format);
    mergeCurrentCharFormat(format);
}


void HTMLChatEdit::initActions() {
    
    //font style
    actionTextBold = new QAction(QIcon(iconPath + "textbold.png"), tr("&Bold"), this);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setCheckable(true);
	
    actionTextItalic = new QAction(QIcon(iconPath + "textitalic.png"), tr("&Italic"), this);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    actionTextItalic->setCheckable(true);
	
    actionTextUnderline = new QAction(QIcon(iconPath + "textunder.png"), tr("&Underline"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    actionTextUnderline->setCheckable(true);

    //align
    QActionGroup * alignActions = new QActionGroup(this);

    actionAlignLeft = new QAction(QIcon(iconPath + "textleft.png"), tr("&Left"), alignActions);
    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setProperty("align", Qt::AlignLeft);
    actionAlignLeft->setCheckable(true);
    
    actionAlignCenter = new QAction(QIcon(iconPath + "textcenter.png"), tr("C&enter"), alignActions);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setProperty("align", Qt::AlignCenter);
    actionAlignCenter->setCheckable(true);
    
    actionAlignRight = new QAction(QIcon(iconPath + "textright.png"), tr("&Right"), alignActions);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setProperty("align", Qt::AlignRight);
    actionAlignRight->setCheckable(true);
    
    actionAlignJustify = new QAction(QIcon(iconPath + "textjustify.png"), tr("&Justify"), alignActions);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setProperty("align", Qt::AlignJustify);
    actionAlignJustify->setCheckable(true);


    //append to toolbar
    toolBar->addAction(actionTextBold);
    toolBar->addAction(actionTextItalic);
    toolBar->addAction(actionTextUnderline);

    toolBar->addSeparator(); 
    
    toolBar->addAction(actionAlignLeft);
    toolBar->addAction(actionAlignCenter);
    toolBar->addAction(actionAlignRight);
    toolBar->addAction(actionAlignJustify);

    toolBar->addSeparator(); 
   

    //connect actions
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
    
    connect(alignActions, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));
}


HTMLChatEdit::~HTMLChatEdit() {
    qDebug() << toHtml();
}





