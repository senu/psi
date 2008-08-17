#include "chatviewfactory.h"
#include "msgmle.h"
#include "psioptions.h"
#include "applicationinfo.h"
#include "urlobject.h"

#include "htmlchattheme.h"


ChatView * ChatViewFactory::createChatView(bool isGroupChat, QString jid,
                                           QWidget* parent, bool* isHTMLChatView,
                                           HTMLThemeManager* themeManager,
                                           IconServer* iconServer) {

    Q_UNUSED(jid); //jid could be used to select jid-based theme.

    bool useHTMLView;
    
    if (isGroupChat) {
        useHTMLView = PsiOptions::instance()->getOption("options.ui.themes.htmlviewinmuc").toBool();
    }
    else {
        useHTMLView = PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool();
    }

    if (useHTMLView) { //create HTMLChatView
        
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

    PlainTextChatTheme theme = createPlainTextChatTheme();
    return new PlainTextChatView(parent, theme);
}


PlainTextChatTheme ChatViewFactory::createPlainTextChatTheme() {
    PlainTextChatTheme theme;

    QFont font;
    font.fromString(PsiOptions::instance()->getOption("options.ui.look.font.chat").toString());
    theme.setChatFont(font);
    theme.setIncomingNickColor(PsiOptions::instance()->getOption("options.ui.look.colors.chat.incoming-nick-color").toString());
    theme.setOutgoingNickColor(PsiOptions::instance()->getOption("options.ui.look.colors.chat.outgoing-nick-color").toString());
    theme.setSpooledNickColor(PsiOptions::instance()->getOption("options.ui.look.colors.chat.spooled-nick-color").toString());
    theme.setSystemMessageColor(PsiOptions::instance()->getOption("options.ui.look.colors.chat.system-message-color").toString());
    theme.setUseChatSaysStyle(PsiOptions::instance()->getOption("options.ui.chat.use-chat-says-style").toBool());

    return theme;
}
