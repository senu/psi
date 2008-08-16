#ifndef HAVE_CHAT_VIEW
#define HAVE_CHAT_VIEW

#include <Qt> 
#include <QWidget> 
#include <QScrollBar> 
#include <QList>

#include "chatevent.h"

class ChatEvent;

/** Abstract ChatView widget */
class ChatView : public QWidget {


    Q_OBJECT

public:
    ChatView(QWidget* parent) : QWidget(parent) {
    qDebug() << "@@@@ MEM WEBKIT: ++++" << "ChatView::ChatView()"; 
    }


    /** 
     * Destructor.
     * 
     * NOTE: events in appendedEvents are not freed, because they can be used in
     * NOTE: another chatView (restoreDataFrom()).
     * NOTE: you have to call deleteChatEvents() to free them.
     */
    virtual ~ChatView() {
    }

    /** 
     * Appends event (filetransfer, mood, etc); adds it to the appendedEvents 
     * 
     * It's ChatView responsibility to free event
     */
    virtual void appendEvent(ChatEvent* event, bool alreadyAppended = false);

    /**
     * Appends message; adds it to the appendedEvents 
     * 
     * It's ChatView responsibility to free event
     */
    virtual void appendMessage(MessageChatEvent* event, bool alreadyAppended = false);

    /** 
     * Clears all messages. All Events will be freed.
     *
     * NOTE: In Psi you should not call this method. Use clear() from ChatDialog, because
     * NOTE: ChatDialog is responsible for message 'successiveness' (making message consecutive)
     * NOTE: so if you call this->clear() ChatDialog could try to attach consecutive message to 
     * NOTE: one that doesn't now exist. If you really need to call clear() here - create signal cleared()
     */
    virtual void clear();

    /** 
     * Initialize ChatView 
     * \param chatInfo contains conversation info (to who, time stared, etc. )*/
    virtual void init(const ChatTheme::ChatInfo& chatInfo);

    /** 
     * (Re)Initialize ChatView; current chatInfo will be used.
     * Events from appendedEvents will be reappended.
     */
    virtual void init() = 0;


    /**
     * This function returns true if vertical scroll bar is 
     * at its maximum position.
     */
    virtual bool atBottom() const = 0;

    /** 
     * Restore chat data (chatInfo, chatEvents) from the other ChatView.
     * (to switch between PlainText and HTML widgets)
     * Explicit copy constructor
     */
    virtual void restoreDataFrom(const ChatView& other);
    
    /** Sets session info */
    ChatTheme::ChatInfo chatInfo() const;
    
    /** Returns session info */
    void setChatInfo(ChatTheme::ChatInfo chatInfo);

    /** 
     * Returns true if \param str was found in ChatView and selects the match visually.
     * 
     * if \param startFromBeginning is true, search will be performed from the beginning of chatView
     */
    virtual bool internalFind(const QString& str, bool startFromBeginning = false) = 0;

    /** This property holds whether there is any text selected. */
    virtual bool hasSelectedText() const = 0;
    
    /** Copies selected text to clipboard */
    virtual void copySelectedText() = 0;

    /** Removes/hides old trackBar (if it exist) and inserts trackBar at the bottom of ChatView */
    virtual void updateTrackBar() = 0;

    /** Clears appendedEvents and free events */
    void deleteChatEvents();

signals:

    /** You cannot append messages until ChatView is ready (synchronization with Webkit) */
    void initDocumentFinished();
    
    /** Emmited whenever the ChatView selection changes*/
    void selectionChanged();
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
    QList <AbstractChatEvent*> appendedEvents;

    /** Reappends events */
    void reappendEvents();

};
#endif

