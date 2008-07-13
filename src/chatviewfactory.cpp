#include "chatviewfactory.h"
#include "msgmle.h"
#include "psioptions.h"

#include "htmlChatTheme.h"


ChatView * ChatViewFactory::createChatView(bool isGroupChat, QString jid, QWidget * parent) {
    //TODO dont die if...
    if (PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool()) {
        HTMLChatTheme theme("/home/senu/dev/psi/gsoc/repo/psi-fork/src/themes/Pro.uss/");
        return new HTMLChatView(parent, theme, "/home/senu/dev/psi/gsoc/repo/psi-fork/src/");
    }
    return new __PlainTextChatView(parent);
}