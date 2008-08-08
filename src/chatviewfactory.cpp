#include "chatviewfactory.h"
#include "msgmle.h"
#include "psioptions.h"
#include "applicationinfo.h"
#include "urlobject.h"

#include "htmlChatTheme.h"


ChatView * ChatViewFactory::createChatView(bool isGroupChat, QString jid,
                                           QWidget* parent, bool* isHTMLChatView, 
                                           HTMLThemeManager* themeManager, 
                                           IconServer* iconServer) {
    
    bool useHTMLView = PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool();
    
    if (isGroupChat) {
        useHTMLView = PsiOptions::instance()->getOption("options.ui.themes.htmlviewinmuc").toBool();
    }
    
    if (useHTMLView) {

        QString themeName(PsiOptions::instance()->getOption("options.ui.themes.themename").toString());
        QString themeVariant(PsiOptions::instance()->getOption("options.ui.themes.variantname").toString());

        HTMLChatTheme theme(themeManager->getTheme(themeName, themeVariant));

        if (theme.isValid()) {
            *isHTMLChatView = true;
            
            HTMLChatView * view = new HTMLChatView(parent, theme, iconServer);
            QObject::connect(view, SIGNAL(openURL(QString)), URLObject::getInstance(), SIGNAL(openURL(QString)));
            
            return view; 
        } //else fallback (old, PlainTextChatView) ChatView is created

        qDebug() << "WARNING: loading theme:" << themeName << themeVariant << "failed. PlainTextChatView is used as a ChatView";
    }
    
    *isHTMLChatView = false;
    
    PlainTextChatTheme theme;
    //TODO 37
    //TODO 71
    
    QFont font;
    font.fromString(PsiOptions::instance()->getOption("options.ui.look.font.chat").toString());
    theme.setChatFont(font);
    theme.setIncomingNickColor("#0000FF");
    theme.setOutgoingNickColor("#FF0000");
    theme.setSpooledNickColor("#008000");
    theme.setSystemMessageColor("#008000");
    theme.setUseChatSaysStyle(PsiOptions::instance()->getOption("options.ui.chat.use-chat-says-style").toBool());
    
    return new PlainTextChatView(parent, theme);
}
