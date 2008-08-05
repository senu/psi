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
    //TODO 10 fallback 
    
    bool useHTMLView = PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool();
    
    if (isGroupChat) {
        useHTMLView = PsiOptions::instance()->getOption("options.ui.themes.htmlviewinmuc").toBool();
    }
    
    if (useHTMLView) {

        QString themeName(PsiOptions::instance()->getOption("options.ui.themes.themename").toString());
        QString themeVariant(PsiOptions::instance()->getOption("options.ui.themes.variantname").toString());

        HTMLChatTheme theme(themeManager->getTheme(themeName, themeVariant));

        *isHTMLChatView = true;
        HTMLChatView * view = new HTMLChatView(parent, theme, iconServer, ApplicationInfo::homeDir());\
            
        QObject::connect(view, SIGNAL(openURL(QString)), URLObject::getInstance(), SIGNAL(openURL(QString)));
        
        return view;
    }
    *isHTMLChatView = false;
    return new __PlainTextChatView(parent);
}
