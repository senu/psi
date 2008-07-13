#ifndef _CHATVIEWPROXY_H
#define	_CHATVIEWPROXY_H

#include <QWidget>
#include <QLayout>

#include "chatView.h"


/** Adapter to change ChatViews in runtime/embed them with qt designer */
class ChatViewProxy : public QWidget {

    Q_OBJECT
public:
    ChatViewProxy(QWidget* parent);

    /** Returns encapsulated ChatView widget */
    ChatView* chatView() const;
private:
    ChatView * _chatView;
    QLayout* layout;

};


#endif

