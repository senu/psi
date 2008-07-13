#include "chatviewproxy.h"
#include "chatviewfactory.h"


ChatViewProxy::ChatViewProxy(QWidget* parent)
: QWidget(parent) {

    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    
    _chatView = ChatViewFactory::createChatView(false, "TODO@jabber.org", this);
//    _chatView->setGeometry(0,20,400,440);
    _chatView->init();
    qDebug() << "proxy" << geometry();
}


ChatView* ChatViewProxy::chatView() const {
    return _chatView;
}