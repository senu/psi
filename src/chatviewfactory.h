#ifndef _CHATVIEWFACTORY_H
#define	_CHATVIEWFACTORY_H

#include <QString>
#include "chatView.h"
#include "htmlChatView.h"
#include "plaintextchatview.h"
#include "htmlthememanager.h"


/** Crates appropriate ChavView (with ChatTheme) based on chat type and/or jid */
class ChatViewFactory {

public:


    /** Creates ChatView
     * \param isGroupChat determines chat type 
     * \param jid is destination name or muc channel 
     * \param parent will be passed to created ChatView
     * \param isHTMLChatView will be true <=> crated ChatView is a HTMLChatView
     * \param themeManager is needed because Kev didnt want it as singleton
     * \param iconServer will be used in HTMLChatView for serving icons purporses
     */
    static ChatView* createChatView(bool isGroupChat, QString jid, QWidget * parent,
                                     bool * isHTMLChatView, HTMLThemeManager* themeManager,
                                     IconServer* iconServer);

    /** Creates ChatTheme based on PsiOptions */
    static PlainTextChatTheme createPlainTextChatTheme();

};


#endif

