#include "chatviewproxy.h"
#include "chatviewfactory.h"
#include "psioptions.h"


ChatViewProxy::ChatViewProxy(QWidget* parent)
: QWidget(parent) {

    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    _chatView = createChatView();

    setLayout(layout);

    connect(PsiOptions::instance(), SIGNAL(optionChanged(const QString&)), SLOT(optionsChanged()));
}


ChatView* ChatViewProxy::chatView() const {
    return _chatView;
}


void ChatViewProxy::optionsChanged() {
    if (PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool() != isHTMLChatView) {
        ChatView * newView = createChatView();
        newView->restoreDataFrom(*_chatView);
        newView->init();
        
        delete _chatView;
        _chatView = newView;
    }
}


ChatView * ChatViewProxy::createChatView() {
    ChatView * newView = ChatViewFactory::createChatView(false, "TODO@jabber.org", this, &isHTMLChatView);
    layout->addWidget(newView);
    return newView;
}
