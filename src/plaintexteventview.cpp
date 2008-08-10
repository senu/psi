#include "plaintexteventview.h"
#include <QtDebug>


PlainTextEventView::PlainTextEventView(QWidget* parent) : PsiTextView(parent) {
}


void PlainTextEventView::displayText(const QString& xhtmlText) {
    clear();
    appendText("<qt>" + xhtmlText + "</qt>");
}