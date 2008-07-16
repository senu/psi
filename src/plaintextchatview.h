#ifndef _PLAINTEXTCHATVIEW_H
#define	_PLAINTEXTCHATVIEW_H

#include <QWidget>
#include <QScrollBar>
#include <QtDebug>
#include <QVBoxLayout>
#include "chatView.h"
#include "psitextview.h"
#include "psichatedit.h"
#include "plaintextchattheme.h"


//#include "msgmle.h"


class ChatView;
class ChatEdit;


/** used only in chatdlg */
class __PlainTextChatView : public ChatView {

    Q_OBJECT
public:
    void appendEvent(const ChatEvent* event, bool alreadyAppended = false);
    void appendMessage(const MessageChatEvent* event, bool alreadyAppended = false);

    void clear();

    void init();


    void setReadOnly(bool readOnly);


    __PlainTextChatView(QWidget *parent);


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


    void appendText(const QString &text) {
        bool doScrollToBottom = atBottom();

        // prevent scrolling back to selected text when 
        // restoring selection
        int scrollbarValue = verticalScrollBar()->value();

        textview.appendText(text);

        if (doScrollToBottom)
            scrollToBottom();
        else
            verticalScrollBar()->setValue(scrollbarValue);
    }

    //reimplemented

    /** Used for scrollToTop/Bottom */
    QScrollBar * verticalScrollBar() const;


    QSize sizeHint() const { //TODO
        qDebug() << "sizeHint" << minimumSizeHint() << textview.minimumSizeHint();
        return minimumSizeHint();
    }

    /**
     * This function returns true if vertical scroll bar is 
     * at its maximum position.
     */
    bool atBottom() const;

    public


slots:
    /**
     * Scrolls the vertical scroll bar to its maximum position i.e. to the bottom.
     */
    virtual void scrollToBottom();

    /**
     * Scrolls the vertical scroll bar to its minimum position i.e. to the top.
     */
    virtual void scrollToTop();


protected:
    PsiTextView textview;
    PlainTextChatTheme theme;
    QVBoxLayout *layout;


};


#endif	

