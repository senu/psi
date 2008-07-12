#ifndef HAVE_CHAT_VIEW
#define HAVE_CHAT_VIEW

#include <Qt> 
#include <QWidget> 
#include <QScrollBar> 

#include "chatEvent.h"

class ChatEvent;


/** Abstract ChatView widget */
class ChatView : public QWidget {


    Q_OBJECT

public:
    ChatView(QWidget* parent) : QWidget(parent) {
    }


    virtual ~ChatView() {
    }

    virtual void appendEvent(const ChatEvent* event) = 0;
    virtual void appendMessage(const MessageChatEvent* event) = 0;

    /** clears all messges */
    virtual void clear() = 0;

    /** Initialize ChatView */
    virtual void init() = 0;


    /**
     * This function returns true if vertical scroll bar is 
     * at its maximum position.
     */
    virtual bool atBottom() const = 0; 
    public


slots:
    /**
     * Scrolls the vertical scroll bar to its maximum position i.e. to the bottom.
     */
    virtual void scrollToBottom() = 0;

    /**
     * Scrolls the vertical scroll bar to its minimum position i.e. to the top.
     */
    virtual void scrollToTop() = 0;

};
#endif

