#include "chatviewfactory.h"
#include "msgmle.h"
#include "psioptions.h"
#include "applicationinfo.h"

#include "htmlChatTheme.h"


ChatView * ChatViewFactory::createChatView(bool isGroupChat, QString jid,
                                           QWidget* parent, bool* isHTMLChatView, HTMLThemeManager* themeManager) {
    
    if (PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool()) {

        QString themeName = PsiOptions::instance()->getOption("options.ui.themes.themename").toString();

        HTMLChatTheme theme(themeManager->getTheme(themeName));
        theme.setCurrentVariant(PsiOptions::instance()->getOption("options.ui.themes.variantname").toString());

        *isHTMLChatView = true;
        return new HTMLChatView(parent, theme, ApplicationInfo::homeDir());
    }
    *isHTMLChatView = false;
    return new __PlainTextChatView(parent);
}
