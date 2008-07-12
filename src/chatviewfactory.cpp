#include "chatviewfactory.h"
#include "msgmle.h"

#include "htmlChatTheme.h"

ChatView * ChatViewFactory::createChatView(bool isGroupChat, QString jid, QWidget * parent) {
    //TODO dont die if...
    HTMLChatTheme theme("/home/senu/dev/psi/gsoc/repo/psi-fork/src/themes/Pro.uss/");
    return new HTMLChatView(parent, theme, "/home/senu/dev/psi/gsoc/repo/psi-fork/src/");
    //new __PlainTextChatView(parent);
}