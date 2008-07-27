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
     * iconServer and themeManager are required by ChatViewFactory
     */
    void init(const ChatTheme::ChatInfo& chatInfo, HTMLThemeManager* themeManager, IconServer* iconServer);
    
public slots:
	void optionsChanged(const QString& optionName);
    
private:
    ChatView* _chatView;
    
    /** Will be passed to ChatViewFactory */
    HTMLThemeManager* themeManager;
    
    /** Will be passed to ChatViewFactory */
    IconServer* iconServer;

    /** Is current chatView() instance of HTMLChatView? */
    bool isHTMLChatView;

    /** Creates new ChatView using ChatViewFactory and updates layout */
    ChatView* createChatView();
    
    QLayout* layout;

};


#endif

