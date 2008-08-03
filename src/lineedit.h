#ifndef _LINEEDIT_H
#define	_LINEEDIT_H

#include "genericlineedit.h"


/** AutoResizing HTMLChatEdit */
class LineEdit : public GenericLineEdit<HTMLChatEdit> { //TODO name

    Q_OBJECT

public:
    LineEdit(QWidget* parent);

    private
slots:
    void callRecalculateSize();
    void callUpdateScrollBar();

};

/** AutoResizing HTMLChatEdit */
class PlainLineEdit : public GenericLineEdit<ChatEdit> { 

    Q_OBJECT

public:
    PlainLineEdit(QWidget* parent);

    private
slots:
    void callRecalculateSize();
    void callUpdateScrollBar();

};

#endif

