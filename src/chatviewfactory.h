#ifndef _CHATVIEWFACTORY_H
#define	_CHATVIEWFACTORY_H

#include <QString>
#include "chatView.h"
#include "htmlChatView.h"
#include "plaintextchatview.h"


/** Crates appropriate ChavView (with ChatTheme) based on chat type and/or jid */
class ChatViewFactory {

public:


    /** Creates ChatView
     * \param isGroupChat determines chat type 
     * \param jid is destination name or muc channel 
     * \param parent will be passed to created ChatView
     * \param isHTMLChatView will be true <=> crated ChatView is a HTMLChatView
     */
    static ChatView * createChatView(bool isGroupChat, QString jid, QWidget * parent, bool * isHTMLChatView);

};


#endif

