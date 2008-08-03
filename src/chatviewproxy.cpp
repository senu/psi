#include "chatviewproxy.h"
#include "chatviewfactory.h"
#include "psioptions.h"


ChatViewProxy::ChatViewProxy(QWidget* parent)
: QWidget(parent), _chatView(0), themeManager(0), iconServer(0) {

    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);

    connect(PsiOptions::instance(), SIGNAL(optionChanged(const QString&)), SLOT(optionsChanged(const QString&)));
}


ChatView* ChatViewProxy::chatView() const {
    return _chatView;
}


void ChatViewProxy::init(const ChatTheme::ChatInfo& chatInfo, bool inGroupChat_, HTMLThemeManager* themeManager_, IconServer* iconServer_) {

    themeManager = themeManager_;
    iconServer = iconServer_;
    inGroupChat = inGroupChat_;
    jid = chatInfo.destinationDisplayName;
    
    _chatView = createChatView(inGroupChat, jid);
    _chatView->init(chatInfo);
}


void ChatViewProxy::optionsChanged(const QString& optionName) {
    qDebug() << optionName;
    if (!_chatView || !optionName.startsWith("options.ui.themes")) {
        return;
    }
    
    if (PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool() != isHTMLChatView) {
        ChatView * newView = createChatView(inGroupChat, jid);
        newView->restoreDataFrom(*_chatView);
        newView->init();

        delete _chatView;
        _chatView = newView;
    }
    
    if (!optionName.startsWith("options.ui.themes.themename") && 
        !optionName.startsWith("options.ui.themes.variantname")) {
        return;
    }

    //TODO ? muc/chat/per group/per regexp settings
    if(isHTMLChatView) { //theme change?
        qDebug() << "themeChanged?" << PsiOptions::instance()->getOption("options.ui.themes.themename").toString();
        dynamic_cast<HTMLChatView *> (_chatView)->setTheme(themeManager->getTheme(
            PsiOptions::instance()->getOption("options.ui.themes.themename").toString(), //TODO pointers
            PsiOptions::instance()->getOption("options.ui.themes.variantname").toString())); 
    }
}


ChatView * ChatViewProxy::createChatView(bool inGroupChat, const QString& jid) {
    ChatView * newView = ChatViewFactory::createChatView(inGroupChat, jid, this, &isHTMLChatView, 
                                                         themeManager, iconServer);
    layout->addWidget(newView);
    return newView;
}
