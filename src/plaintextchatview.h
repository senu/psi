#ifndef _PLAINTEXTCHATVIEW_H
#define	_PLAINTEXTCHATVIEW_H

#include <QWidget>
#include "chatView.h"
#include "psitextview.h"

//#include "msgmle.h"


class ChatView;


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

public:


    void setReadOnly(bool readOnly) {
        textview.setReadOnly(readOnly);
    }


    void PlainTextChatView::setDialog(QWidget* dialog) {
        dialog_ = dialog;
    }


    __PlainTextChatView(QWidget *parent) : PlainTextChatView__(parent), _dialog(0), textview(parent) {
    }

protected:
    PsiTextView textview;
    QWidget* _dialog;

};


#endif	

