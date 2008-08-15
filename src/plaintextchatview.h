#ifndef _PLAINTEXTCHATVIEW_H
#define	_PLAINTEXTCHATVIEW_H

#include <QWidget>
#include <QScrollBar>
#include <QtDebug>
#include <QVBoxLayout>
#include "chatView.h"
#include "psitextview.h"
#include "psichatedit.h"
#include "plaintextchattheme.h"

class ChatView;
class ChatEdit;


/**
 * PlainText (old) version of ChatView.
 *
 * It has smaller memory footprint (in comparison to HTMLChatView) but is uglier. 
 */
class PlainTextChatView : public ChatView {

    Q_OBJECT
public:
    void appendEvent(ChatEvent* event, bool alreadyAppended = false);
    void appendMessage(MessageChatEvent* event, bool alreadyAppended = false);

    void init();

    PlainTextChatView(QWidget *parent, PlainTextChatTheme theme);

    /** Sets theme (if needed) */
    void setTheme(const PlainTextChatTheme& theme);

    /** Used for scrollToTop/Bottom/Up/Down */
    QScrollBar * verticalScrollBar() const;


    //reimplemented
    QSize sizeHint() const;

    void scrollUp();
    void scrollDown();

    /**
     * This function returns true if vertical scroll bar is 
     * at its maximum position.
     */
    bool atBottom() const;

    void clear();

    bool internalFind(const QString& str, bool startFromBeginning = false);
    bool hasSelectedText() const;
    void copySelectedText();

    void updateTrackBar();

    public
slots:
    /**
     * Scrolls the vertical scroll bar to its maximum position i.e. to the bottom.
     */
    void scrollToBottom();

    /**
     * Scrolls the vertical scroll bar to its minimum position i.e. to the top.
     */
    void scrollToTop();


protected:

    void appendText(const QString &text);

    PsiTextView textview;
    PlainTextChatTheme theme;
    QVBoxLayout *layout;

    /** Holds position of trackBar (0 if no trackBar) */
    int oldTrackBarPosition;


};


#endif	

