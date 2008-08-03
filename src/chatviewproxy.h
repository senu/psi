#ifndef _CHATVIEWPROXY_H
#define	_CHATVIEWPROXY_H

#include <QWidget>
#include <QLayout>

#include "chatView.h"
#include "htmlthememanager.h"
#include "iconserver.h"


/** Adapter to change ChatViews in runtime/embed them with qt designer */
class ChatViewProxy : public QWidget {

    Q_OBJECT
public:
    /** Constructor; you have to call init() to use ChatViewProxy */
    ChatViewProxy(QWidget* parent);

    /** Returns encapsulated ChatView widget; you have to call init(ci) after that! */
    ChatView* chatView() const;

    /** 
     * Initialize ChatView
     *
     * \param chatInfo (chat session information) will be passed to ChatView
     * \param iconServer and 
     * \param themeManager are required by ChatViewFactory
     * \param inGroupChat should be true if ChatViewProxy is used in MUC dialog
     */
    void init(const ChatTheme::ChatInfo& chatInfo, bool inGroupChat,
              HTMLThemeManager* themeManager_, IconServer* iconServer_);

    public
slots:
    void optionsChanged(const QString& optionName);

private:
    ChatView* _chatView;

    /** Will be passed to ChatViewFactory */
    HTMLThemeManager* themeManager;

    /** Will be passed to ChatViewFactory */
    IconServer* iconServer;

    /** Is current chatView() instance of HTMLChatView? */
    bool isHTMLChatView;


    /**
     * Creates new ChatView using ChatViewFactory and updates layout.
     *
     * \param inGroupChat indcates place where ChatView will be used
     * \param jid indicates to whom we are talking or muc room name
     */
    ChatView* createChatView(bool inGroupChat, const QString& jid);

    QLayout* layout;

    bool inGroupChat;
    QString jid;

};


#endif

