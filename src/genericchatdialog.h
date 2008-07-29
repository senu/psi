#ifndef _GENERICCHATDIALOG_H
#define	_GENERICCHATDIALOG_H

#include <QObject>


#include "xmpp_message.h"

#include "defaulthtmltextformatter.h"
#include "messageValidator.h"
#include "chatView.h"
#include "psichatedit.h"
#include "statusChatEvent.h"


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
    ~GenericChatDialog() {};

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

    /** Returns dialog's ChatView */
	virtual ChatView* chatView() const = 0;
    
    /** Returns dialog's ChatEdit */
	virtual ChatEdit* chatEdit() const = 0;

    //defined in ChatDlg
    QString messageTextGC(const XMPP::Message& m);
    bool isEmoteMessageGC(const XMPP::Message& m);

    
    //fields
    /** Validates XHTML-IM messages */
    MessageValidator messageValidator_;

    /** Does emoticonify, linkify, etc in XHTML-IM messages */
    DefaultHTMLTextFormatter textFormatter_;
    
    /** Indicates if next message should be consecutive */
    LastEventOwner lastEventOwner;

    /** Timestamp of last chat event */
    QDateTime lastMsgTime;
};

#endif	

