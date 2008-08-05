#ifndef _LINEEDIT_H
#define	_LINEEDIT_H

#include "genericlineedit.h"


/** Auto-resizing HTMLChatEdit */
class HTMLLineEdit : public GenericLineEdit<HTMLChatEdit> {

    Q_OBJECT

public:
    HTMLLineEdit(QWidget* parent);

    private
slots:
    void callRecalculateSize();
    void callUpdateScrollBar();

};

/** Auto-resizing  Text ChatEdit */
class LineEdit : public GenericLineEdit<ChatEdit> { 

    Q_OBJECT

public:
    LineEdit(QWidget* parent);

    private
slots:
    void callRecalculateSize();
    void callUpdateScrollBar();

};

#endif

