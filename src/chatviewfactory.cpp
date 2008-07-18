#include "chatviewfactory.h"
#include "msgmle.h"
#include "psioptions.h"
#include "applicationinfo.h"

#include "htmlChatTheme.h"


ChatView * ChatViewFactory::createChatView(bool isGroupChat, QString jid,
                                           QWidget* parent, bool* isHTMLChatView, HTMLThemeManager* themeManager) {
    //TODO fallback 
    if (PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool()) {

        QString themeName(PsiOptions::instance()->getOption("options.ui.themes.themename").toString());
        QString themeVariant(PsiOptions::instance()->getOption("options.ui.themes.variantname").toString());

        HTMLChatTheme theme(themeManager->getTheme(themeName,themeVariant));

        *isHTMLChatView = true;
        return new HTMLChatView(parent, theme, ApplicationInfo::homeDir());
    }
    *isHTMLChatView = false;
    return new __PlainTextChatView(parent);
}
