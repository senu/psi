/*
 * eventdlg.h - dialog for sending / receiving messages and events
 * Copyright (C) 2001, 2002  Justin Karneges
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef EVENTDLG_H
#define EVENTDLG_H

#include <QLineEdit>
#include <q3listview.h>

#include "xmpp_url.h"
#include "xmpp_rosterx.h"
#include "advwidget.h"
#include "userlist.h"
#include "addurldlg.h"
#include "htmlchatedit.h"
#include "eventview.h"

class QDateTime;
class QStringList;
class Q3PopupMenu;
class PsiEvent;
class PsiCon;
class PsiAccount;
class PsiIcon;
class EventDlg;
namespace XMPP {
	class Jid;
	class XData;
}
class PsiHttpAuthRequest;

using namespace XMPP;

class ELineEdit : public QLineEdit
{
	Q_OBJECT
public:
	ELineEdit(EventDlg *parent, const char *name=0);

signals:
	void changeResource(const QString &);
	void tryComplete();

protected:
	// reimplemented
	void dragEnterEvent(QDragEnterEvent *);
	void dropEvent(QDropEvent *);
	void keyPressEvent(QKeyEvent *);
	Q3PopupMenu *createPopupMenu();

private slots:
	void resourceMenuActivated(int);

private:
	UserResourceList url;
};

class AttachView : public Q3ListView
{
	Q_OBJECT
public:
	AttachView(QWidget *parent=0, const char *name=0);
	~AttachView();

	void setReadOnly(bool);
	void urlAdd(const QString &, const QString &);
	void gcAdd(const QString &, const QString& = QString(), const QString& = QString(), const QString& = QString());

	UrlList urlList() const;
	void addUrlList(const UrlList &);

signals:
	void childCountChanged();
	void actionGCJoin(const QString &, const QString&);

private slots:
	void qlv_context(Q3ListViewItem *, const QPoint &, int);
	void qlv_doubleClicked(Q3ListViewItem *);

private:
	bool v_readOnly;

	void goURL(const QString &);
};


class EventDlg : public AdvancedWidget<QWidget>
{
	Q_OBJECT
public:
	// compose
	EventDlg(const QString &, PsiCon *, PsiAccount *);
	// read
	EventDlg(const Jid &, PsiAccount *, bool unique);
	~EventDlg();

	void setSubject(const QString &);
	void setThread(const QString &);
	void setUrlOnShow();

    /** 
     * Clears editor() contents and put \param into editor(). 
     * 
     * used in quote/reply
     * \param text can be XHTML/rich text, so it has to be escaped
     */
    void setEditedText(const QString& text);

	PsiAccount *psiAccount();

	static QSize defaultSize();

signals:
	void aChat(const Jid& jid);
	void aReply(const Jid &jid, const QString &body, const QString &subject, const QString &thread);
	void aReadNext(const Jid &);
	void aDeny(const Jid &);
	void aAuth(const Jid &);
	void aHttpConfirm(const PsiHttpAuthRequest &);
	void aHttpDeny(const PsiHttpAuthRequest &);
	void aRosterExchange(const RosterExchangeItems &);
	void aFormSubmit(const XData&, const QString&, const Jid&);
	void aFormCancel(const XData&, const QString&, const Jid&);

protected:
	// reimplemented
	void showEvent(QShowEvent *);
	void resizeEvent(QResizeEvent *);
	void keyPressEvent(QKeyEvent *);
	void closeEvent(QCloseEvent *);
    
    /** Returns pointer to event editor (if in composing mode), NULL otherwise */
    ChatEdit* editor() const;
    
    /** Returns pointer to event viewer (if in viewing mode), NULL otherwise */
    EventView* view() const;

    /** Returns editor() if in composing mode, view() otherwise */
    QWidget* editorOrView() const;
    
    /** 
     * Displays \param text (text string can be RichText or XHTML) in the view().
     *
     * \param text must be html-escaped.
     * 
     * It will be display in Webkit view() or in QTextEdit view().
     * You should only message content. For example: <p>txt</p> instead of <html><body>...</body></html>
     */
    void displayText(const QString &text); //qwer !

public slots:
	void optionsUpdate();
	void closeAfterReply();
	void updateContact(const Jid &);
	void updateEvent(PsiEvent *);
	void updateReadNext(PsiIcon *, int);
	void actionGCJoin(const QString &, const QString&);

private slots:
	void to_textChanged(const QString &);
	void to_changeResource(const QString &);
    
    /** To: lineEdit has JID completion */
	void to_tryComplete();
	void updateIdentity(PsiAccount *);
	void updateIdentityVisibility();
	void accountUpdatedActivity();
	void doWhois(bool force=false);
	void doSend();
	void doReadNext();
	void doChat();
	void doReply();
	void doQuote();
	void doDeny();
	void doAuth();
	void doHttpConfirm();
	void doHttpDeny();
	void doInfo();
	void doHistory();
	void showHideAttachView();
	void addUrl();
	void doFormSubmit();
	void doFormCancel();

	void updatePGP();
	void encryptedMessageSent(int, bool, int, const QString &);
	void trySendEncryptedNext();

public:
	class Private;
private:
	Private *d;

	void doneSend();

	void init();
    
    /** Comma separated strings */
	QStringList stringToList(const QString &, bool enc=true) const;
	QString findJidInString(const QString &) const;
	QString expandAddresses(const QString &, bool enc=true) const;

    /** To: lineEdit has JID completion */
	void buildCompletionList();
	void setAccount(PsiAccount *);
	void setTime(const QDateTime &, bool late=false);

	friend class ELineEdit;
	UserResourceList getResources(const QString &) const;
	QString jidToString(const Jid &, const QString &r="") const;
};

#endif
