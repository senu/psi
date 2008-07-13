#include "chatviewfactory.h"
#include "msgmle.h"
#include "psioptions.h"
#include "applicationinfo.h"

#include "htmlChatTheme.h"


ChatView * ChatViewFactory::createChatView(bool isGroupChat, QString jid, QWidget * parent) {
    //TODO dont die if...
    if (PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool()) {

        QString themePath = PsiOptions::instance()->getOption("options.ui.themes.themepath").toString();
        
        HTMLChatTheme theme(themePath);
        theme.setCurrentVariant(PsiOptions::instance()->getOption("options.ui.themes.variantname").toString());

        return new HTMLChatView(parent, theme, ApplicationInfo::homeDir());
    }
    return new __PlainTextChatView(parent);
}
