#include <QTimer>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include "genericlineedit.h"
#include "psichatedit.h"
#include "lineedit.h"
#include "htmlchatedit.h"

class HTMLChatEdit;


LineEdit::LineEdit(QWidget* parent) : GenericLineEdit<HTMLChatEdit>(parent) {
    connect(this, SIGNAL(textChanged()), SLOT(callRecalculateSize()));
    QTimer::singleShot(0, this, SLOT(callRecalculateSize()));
}


void LineEdit::callUpdateScrollBar() {
    updateScrollBar();
}

void LineEdit::callRecalculateSize() {
    recalculateSize();
}

//It's still copy-paste but only 2 methods
PlainLineEdit::PlainLineEdit(QWidget* parent) : GenericLineEdit<ChatEdit>(parent) {
    connect(this, SIGNAL(textChanged()), SLOT(callRecalculateSize()));
    QTimer::singleShot(0, this, SLOT(callRecalculateSize()));
}


void PlainLineEdit::callUpdateScrollBar() {
    updateScrollBar();
}

void PlainLineEdit::callRecalculateSize() {
    recalculateSize();
}