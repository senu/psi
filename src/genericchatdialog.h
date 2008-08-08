#ifndef _GENERICCHATDIALOG_H
#define	_GENERICCHATDIALOG_H

#include <QObject>
#include <QPointer>


#include "xmpp_message.h"

#include "defaulthtmltextformatter.h"
#include "messageValidator.h"
#include "chatView.h"
#include "psichatedit.h"
#include "statusChatEvent.h"
#include "finddialog.h"

class GenericChatDialogQObject;


/**
 * A step towards better GCMainDlg.
 *
 * Currently ChatDlg is a base class of PsiChatDlg.
 * Currently ChatDlg is not a base class of GCMainDlg.
 *
 * GenericChatDialog is a base class of PsiChatDlg and GCMainDlg and in the future
 * it will replace ChatDlg
 * 
 * Methods used in GCMainDlg/ChatDlg but defined here don't have to end with GC (Generic Chat) 
 * but they do, because it's less confusing and error prone. 
 * 
 **/
class GenericChatDialog {

public:
    GenericChatDialog();
    ~GenericChatDialog();

    /** 
     * Opens Find Dialog.
     *
     * You have to connect findDialog -> SIGNAL(find(const QString &)) with doFindGC 
     * \param chatDialogWidget points to ChatDialog QWidget (GenericChatDlg cannot be QObject).
     */
    void openFindGC(QWidget* chatDialogWidget);

    /** Performs search for str in ChatView */
    void doFindGC(const QString& str);

protected:


    /** Indicates if next message should be consecutive (who was last owner) */
    enum LastEventOwner {

        Incoming,
        Outgoing,
        Other /** first message or ChatEvent */
    };


    /** 
     * Returns true if next message should be consecutive
     * \param local indicates if it's our message 
     */
    bool doConsecutiveMessage(const QDateTime& time, bool local);

    /** Updates information about last ChatEvent; called after appending an event */
    void updateLastMsgTimeAndOwner(const QDateTime& t, LastEventOwner owner);

    /** Status must be translated because we don't want Iris stuff in ChatView */
    StatusChatEvent::StatusEventType statusToChatViewStatus(int status) const;

    /** Gives the ChatView focus when text is selected */
    void logSelectionChanged();

    /** Returns dialog's ChatView */
    virtual ChatView* chatView() const = 0;

    /** Returns dialog's ChatEdit */
    virtual ChatEdit* chatEdit() const = 0;
    
    /**
     * Handle KeyPress events that happen in ChatEdit widget. This is used to 
     * 'fix' the copy shortcut.
     *
     * \param event received event
     *
     * Returns true if copy was performed.
     */
    bool handleCopyEvent(QEvent *event);

    /** Returns formatted message body */
    QString messageText(const XMPP::Message& m);
    
    /** Returns true if m is a emote (/me) message */
    bool isEmoteMessage(const XMPP::Message& m);

    /** Does emoticonify, linkify, etc in XHTML-IM messages */
    virtual DefaultHTMLTextFormatter * textFormatter() = 0;
    
    //fields
    
    /** Validates XHTML-IM messages */
    MessageValidator messageValidator_;

    /** Indicates if next message should be consecutive */
    LastEventOwner lastEventOwner;

    /** Timestamp of last chat event */
    QDateTime lastMsgTime;

    /** Pointer to Find Dialog */
    QPointer<FindDialog> findDialog;

    /** Last searched string*/
    QString lastSearch;

    /** Nasty hack to avoid virtual inheritance and linker/c++ templates errors*/
    GenericChatDialogQObject* gcObject;

    friend class GenericChatDialogQObject;
};


/** [Hack - GenericChatDlg cannot inherit from QObject] contains signals and slots */
class GenericChatDialogQObject : public QObject {


    Q_OBJECT
public:
    GenericChatDialogQObject(GenericChatDialog* dlg_) : dlg(dlg_) {
    }


    public


slots:
    /** Gives the ChatView focus when text is selected */
    void logSelectionChanged();
    
    /** Sets focus/selection handlers */
    void chatViewCreated();
    
    /** Scrolls ChatView up */
    void scrollUp();
    
    /** Scrolls ChatView down */
    void scrollDown();

private:
    GenericChatDialog* dlg;
};

#endif	

