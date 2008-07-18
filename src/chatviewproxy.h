#ifndef _CHATVIEWPROXY_H
#define	_CHATVIEWPROXY_H

#include <QWidget>
#include <QLayout>

#include "chatView.h"
#include "htmlthememanager.h"


/** Adapter to change ChatViews in runtime/embed them with qt designer */
class ChatViewProxy : public QWidget {

    Q_OBJECT
public:
    ChatViewProxy(QWidget* parent);

    /** Returns encapsulated ChatView widget; you have to call init(ci) after that! */
    ChatView* chatView() const;

    /** Initialize ChatView */
    void init(const ChatTheme::ChatInfo& chatInfo, HTMLThemeManager* themeManager);
    
public slots:
	void optionsChanged();
    
private:
    ChatView* _chatView;
    HTMLThemeManager* themeManager;
    QLayout* layout;

    /** Is current chatView() instance of HTMLChatView? */
    bool isHTMLChatView;

    /** Creates new ChatView using ChatViewFactory and updates layout */
    ChatView* createChatView();

};


#endif

