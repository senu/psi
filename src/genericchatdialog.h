#ifndef _GENERICCHATDIALOG_H
#define	_GENERICCHATDIALOG_H

#include <QObject>
#include <QPointer>


#include "xmpp_message.h"

#include "defaulthtmltextformatter.h"
#include "messageValidator.h"
#include "chatView.h"
#include "psichatedit.h"
#include "statuschatevent.h"
#include "finddialog.h"

class GenericChatDialogQObject;
using XMPP::Jid;


/**
 * A step towards better GCMainDlg.
 *
 * Currently ChatDlg is a base class of PsiChatDlg.
 * Currently ChatDlg is not a base class of GCMainDlg.
 *
 * GenericChatDialog is a base class of ChatDlg and GCMainDlg and in the future
 * it will replace ChatDlg
 * 
 * New ChatDlg/MUC methods should be added here.
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
    void openFindGC(QWidget* chatDialogWidget); //TODO 117

    /** Performs search for str in ChatView */
    void doFindGC(const QString& str);

protected:

    /** 
     * Returns true if next message should be consecutive
     * \param sender determines sender of the message 
     */
    bool doConsecutiveMessage(const QDateTime& time, const Jid& sender);

    /** Updates information about last ChatEvent; called after appending an event */
    void updateLastMsgTimeAndOwner(const QDateTime& t, const Jid& owner);

    /** 
     * Fills User ChatEvent with corresponding data.
     * Fields nick, jid, icons (status and avatar), isLocal and service are updated;
     *
     * \param userInfo will be filled 
     * \param j is jid of user owner/sender
     */
    virtual void fillEventWithUserInfo(UserChatData* userInfo, const Jid& j) = 0;

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

    /** 
     * Returns formatted message body 
     *
     * Plain or XHTML-IM message body is formatted (linkify, emoticonify) and returned.
     */
    QString messageText(const XMPP::Message& m);

    /** Returns true if m is a emote (/me) message */
    bool isEmoteMessage(const XMPP::Message& m);

    /** Does emoticonify, linkify, etc in XHTML-IM messages */
    virtual DefaultHTMLTextFormatter * textFormatter() = 0;

    //fields

    /** Validates XHTML-IM messages */
    MessageValidator messageValidator_;

    /** 
     * Indicates whether next message should be consecutive.
     * 
     * Empty Jid() is used if not applicable.
     */
    Jid lastEventOwner;

    /** Timestamp of last chat event */
    QDateTime lastMsgTime;

    /** Pointer to Find Dialog */
    QPointer<FindDialog> findDialog;

    /** Last searched string*/
    QString lastSearch;

    /** Nasty hack to avoid virtual inheritance and linker/c++ templates errors */
    GenericChatDialogQObject* gcObject;

    /**
     * This property holds whether Psi should send \<message/\> stanza with XHTML-IM extension
     *
     * NOTE: Currently we send XHTML-IM messages only after we get <feature var='http://jabber.org/protocol/xhtml-im'/>
     * NOTE: Disco Info Result
     */
    bool sendXHTML;

    /** Used to convert XML string to DOM document */
    QXmlInputSource xmlSource;
    
    /** Used to convert XML string to DOM document */
    QXmlSimpleReader xmlReader;

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

    /** Ask whether doClear() should be performed and doesClear() */
    void doClearButton();

    /** Clears ChatView and resets message successivenes */
    void doClear();

private:
    GenericChatDialog* dlg;
};

#endif	

