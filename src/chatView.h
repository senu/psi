#ifndef HAVE_CHAT_VIEW
#define HAVE_CHAT_VIEW

#include <Qt> 
#include <QWidget> 
#include <QScrollBar> 
#include <QList>

#include "chatEvent.h"

class ChatEvent;

//TODO chatView.isReady()/signal


/** Abstract ChatView widget */
class ChatView : public QWidget {


    Q_OBJECT

public:
    ChatView(QWidget* parent) : QWidget(parent) {
    }


    virtual ~ChatView() {
    }

    /** Appends event (filetransfer, mood, etc); adds it to the appendedEvents */
    virtual void appendEvent(const ChatEvent* event, bool alreadyAppended = false);

    /** Appends message; adds it to the appendedEvents */
    virtual void appendMessage(const MessageChatEvent* event, bool alreadyAppended = false);

    /** Clears all messages */
    virtual void clear() = 0;

    /** Initialize ChatView 
     * \param chatInfo contains conversation info (to who, time stared, etc. )*/
    virtual void init(const ChatTheme::ChatInfo& chatInfo);

    /** Initialize ChatView; current chatInfo will be used.
     *  Events from appendedEvents will be reappended.
     */
    virtual void init() = 0;


    /**
     * This function returns true if vertical scroll bar is 
     * at its maximum position.
     */
    virtual bool atBottom() const = 0;

    /** Restore chat data (chatInfo, chatEvents) from the other ChatView.
     *  (to switch between PlainText and HTML widgets)
     *  Explicit copy constructor
     */
    virtual void restoreDataFrom(const ChatView& other);
    
    /** Sets session info */
    ChatTheme::ChatInfo chatInfo() const;
    
    /** Returns session info */
    void setChatInfo(ChatTheme::ChatInfo chatInfo);

signals:

    /** You cannot append messages until ChatView is ready (synchronization with Webkit) */
    void initDocumentFinished();

    public


slots:
    /** Scrolls the vertical scroll bar to its maximum position i.e. to the bottom. */
    virtual void scrollToBottom() = 0;

    /** Scrolls the vertical scroll bar to its minimum position i.e. to the top. */
    virtual void scrollToTop() = 0;

    /** Scrolls chatView up */
    virtual void scrollUp() = 0;
    
    /** Scrolls chatView down */
    virtual void scrollDown() = 0;

protected:
    /** Session info */
    ChatTheme::ChatInfo _chatInfo;

    /** Appended events - we need to remember it in case of theme change */
    QList <const AbstractChatEvent*> appendedEvents;

    /** Reappends events */
    void reappendEvents();

};
#endif

