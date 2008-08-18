#include "chatviewproxy.h"
#include "chatviewfactory.h"
#include "psioptions.h"
#include "defaulthtmltextformatter.h"


ChatViewProxy::ChatViewProxy(QWidget* parent)
: QWidget(parent), chatView_(0), themeManager(0), iconServer(0), textFormatter(0) {

    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);

    connect(PsiOptions::instance(), SIGNAL(optionChanged(const QString&)), SLOT(optionsChanged(const QString&)));
}


ChatViewProxy::~ChatViewProxy() {
    if (chatView_) {
        chatView_->deleteChatEvents();
    }
    delete textFormatter;
}


ChatView* ChatViewProxy::chatView() const {
    return chatView_;
}


void ChatViewProxy::init(const ChatTheme::ChatInfo& chatInfo, bool inGroupChat_, HTMLThemeManager* themeManager_, IconServer* iconServer_) {

    themeManager = themeManager_;
    iconServer = iconServer_;
    inGroupChat = inGroupChat_;
    jid = chatInfo.destinationDisplayName;

    chatView_ = createChatView(inGroupChat, jid);
    chatView_->init(chatInfo);
    emit chatViewCreated();
}


void ChatViewProxy::optionsChanged(const QString& optionName) {

    if (!(chatView_ &&
        (optionName.startsWith("options.ui.themes")
        || optionName.startsWith("options.ui.look")
        || optionName.startsWith("options.ui.chat.use-chat-says-style")))) {
        return;
    }

    bool viewWasCreated = false;
    bool newChatType;

    if (inGroupChat) {
        newChatType = PsiOptions::instance()->getOption("options.ui.themes.htmlviewinmuc").toBool();
    }
    else {
        newChatType = PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool();
    }

    if (newChatType != isHTMLChatView) {
        ChatView * newView = createChatView(inGroupChat, jid);
        newView->restoreDataFrom(*chatView_);
        newView->init();

        delete chatView_;
        chatView_ = newView;
        viewWasCreated = true;
    }

    /*
    if (!optionName.startsWith("options.ui.themes.themename") &&
        !optionName.startsWith("options.ui.themes.variantname")) {

        if (viewWasCreated) {
            emit chatViewCreated();
        }
        return;
    }*/

    if (isHTMLChatView) { //change theme if needed
        QString themeName = PsiOptions::instance()->getOption("options.ui.themes.themename").toString();
        QString themeVariant = PsiOptions::instance()->getOption("options.ui.themes.variantname").toString();
        dynamic_cast<HTMLChatView *> (chatView_)->setTheme(themeManager->getTheme(themeName, themeVariant));
    }
    else { //change PlainText theme
        dynamic_cast<PlainTextChatView *> (chatView_)->setTheme(ChatViewFactory::createPlainTextChatTheme());
        //NOTE: maybe I should move it to [HTML]ThemeManager
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

    if (isHTMLChatView) { //NOTE: tbh, we need this only because there's IconTextFormat not QImageTextFormat in PsiChatView
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
