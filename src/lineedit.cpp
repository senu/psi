#include <QTimer>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include "genericlineedit.h"
#include "psichatedit.h"
#include "lineedit.h"
#include "htmlchatedit.h"

class HTMLChatEdit;


HTMLLineEdit::HTMLLineEdit(QWidget* parent) : GenericLineEdit<HTMLChatEdit>(parent) {
    connect(this, SIGNAL(textChanged()), SLOT(callRecalculateSize()));
    QTimer::singleShot(0, this, SLOT(callRecalculateSize()));
}


void HTMLLineEdit::callUpdateScrollBar() {
    updateScrollBar();
}

void HTMLLineEdit::callRecalculateSize() {
    recalculateSize();
}

//It's still copy-paste but now only 2 methods are redundant 
LineEdit::LineEdit(QWidget* parent) : GenericLineEdit<ChatEdit>(parent) {
    connect(this, SIGNAL(textChanged()), SLOT(callRecalculateSize()));
    QTimer::singleShot(0, this, SLOT(callRecalculateSize()));
}


void LineEdit::callUpdateScrollBar() {
    updateScrollBar();
}

void LineEdit::callRecalculateSize() {
    recalculateSize();
}