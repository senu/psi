#include "chatviewproxy.h"
#include "chatviewfactory.h"
#include "psioptions.h"
#include "defaulthtmltextformatter.h"


ChatViewProxy::ChatViewProxy(QWidget* parent)
: QWidget(parent), _chatView(0), themeManager(0), iconServer(0), textFormatter(0) {

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
    emit chatViewCreated();
}


void ChatViewProxy::optionsChanged(const QString& optionName) {
    qDebug() << optionName;
    
    if (!_chatView || !optionName.startsWith("options.ui.themes")) {
        return;
    }

    bool viewWasCreated = false;
    
    if (PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool() != isHTMLChatView) {
        ChatView * newView = createChatView(inGroupChat, jid);
        newView->restoreDataFrom(*_chatView);
        newView->init();

        delete _chatView;
        _chatView = newView;
        viewWasCreated = true;
    }
    
    if (!optionName.startsWith("options.ui.themes.themename") && 
        !optionName.startsWith("options.ui.themes.variantname")) {
        
        if (viewWasCreated) {
            emit chatViewCreated();
        }
        return;
    }

    //TODO + 12 muc/chat/per group/per regexp settings
    if(isHTMLChatView) { //theme change?
        qDebug() << "themeChanged?" << PsiOptions::instance()->getOption("options.ui.themes.themename").toString();
        dynamic_cast<HTMLChatView *> (_chatView)->setTheme(themeManager->getTheme(
            PsiOptions::instance()->getOption("options.ui.themes.themename").toString(), 
            PsiOptions::instance()->getOption("options.ui.themes.variantname").toString())); 
    }
   
    if (viewWasCreated) {
        emit chatViewCreated();
    }
}


ChatView * ChatViewProxy::createChatView(bool inGroupChat, const QString& jid) {
    ChatView * newView = ChatViewFactory::createChatView(inGroupChat, jid, this, &isHTMLChatView, 
                                                         themeManager, iconServer);
    layout->addWidget(newView);
    
    delete textFormatter;
    
    if (isHTMLChatView) { //NOTE: tbh, we need this only because there's IconTextForman not QImageTextFormat in PsiChatView
        textFormatter = new DefaultHTMLTextFormatter(false, true, false, true);   
    }
    else {
        textFormatter = new DefaultHTMLTextFormatter(false, true, false, false);   
    }
    
    return newView;
}

DefaultHTMLTextFormatter* ChatViewProxy::currentTextFormatter() {
    return textFormatter;
}