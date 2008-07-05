#include "htmlchatedit.h"
#include "QtDebug"


HTMLChatEdit::HTMLChatEdit(QWidget* parent) : QTextEdit(parent) {

    this->show();
}


void HTMLChatEdit::textBold() {

	qDebug() << "textBold";

    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
	
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    mergeCurrentCharFormat(format);

}

HTMLChatEdit::~HTMLChatEdit() {
	qDebug() << toHtml();
}





