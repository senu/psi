#ifndef _PLAINTEXTCHATVIEW_H
#define	_PLAINTEXTCHATVIEW_H

#include <QWidget>
#include <QScrollBar>
#include "chatView.h"
#include "psitextview.h"
#include "psichatedit.h"


//#include "msgmle.h"


class ChatView;
class ChatEdit;


class PlainTextChatView__ : public ChatView {

    Q_OBJECT

public:
    PlainTextChatView__(QWidget* parent);

    void appendEvent(const ChatEvent* event);
    void appendMessage(const MessageChatEvent* event);

    void clear();

    void init();

    //~ChatView__()


};


/** used only in chatdlg */
class __PlainTextChatView : public PlainTextChatView__ {

    Q_OBJECT
public:


    void setReadOnly(bool readOnly) {
        textview.setReadOnly(readOnly);
    }


    QScrollBar * verticalScrollBar() const {
        return textview.verticalScrollBar();
    }


    void setDialog(QWidget* dialog) {
        _dialog = dialog;
    }


    __PlainTextChatView(QWidget *parent) : PlainTextChatView__(parent), _dialog(0), textview(parent) {
    }


    //TODO remove/change this
    /**
     * Handle KeyPress events that happen in ChatEdit widget. This is used
     * to 'fix' the copy shortcut.
     * \param object object that should receive the event
     * \param event received event
     * \param chatEdit pointer to the dialog's ChatEdit widget that receives user input
     */
    bool handleCopyEvent(QObject *object, QEvent *event, ChatEdit *chatEdit) {
        if (object == chatEdit && event->type() == QEvent::KeyPress) {
            QKeyEvent *e = (QKeyEvent *) event;
            if ((e->key() == Qt::Key_C && (e->modifiers() & Qt::ControlModifier)) ||
                    (e->key() == Qt::Key_Insert && (e->modifiers() & Qt::ControlModifier))) {
                if (!chatEdit->textCursor().hasSelection() &&
                        textview.textCursor().hasSelection()) {
                    textview.copy();
                    return true;
                }
            }
        }

        return false;
    }

    public


slots:
    /**
     * Scrolls the vertical scroll bar to its maximum position i.e. to the bottom.
     */
    void scrollToBottom() {
        verticalScrollBar()->setValue(verticalScrollBar()->maximum());
    }


    /**
     * Scrolls the vertical scroll bar to its minimum position i.e. to the top.
     */
    void scrollToTop() {
        verticalScrollBar()->setValue(verticalScrollBar()->minimum());
    }


protected:
    QWidget* _dialog;
    PsiTextView textview;

};


#endif	

