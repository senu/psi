/*
 * chatdlg.h - dialog for handling chats
 * Copyright (C) 2001-2007  Justin Karneges, Michail Pishchagin
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

#ifndef CHATDLG_H
#define CHATDLG_H

#include <QContextMenuEvent>
#include <QDragEnterEvent>
#include <QShowEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QDropEvent>
#include <QCloseEvent>

#include "advwidget.h"

#include "tabbablewidget.h"
#include "systemchatevent.h"

#include "chatview.h"
#include "htmlthememanager.h"
#include "iconserver.h"
#include "mood.h"
#include "tune.h"
#include "genericchatdialog.h"


namespace XMPP {
    class Jid;
    class Message;
}
using namespace XMPP;

class PsiAccount;
class UserListItem;
class QDropEvent;
class QDragEnterEvent;
class ChatView;
class ChatEdit;


class ChatDlg : public TabbableWidget, public GenericChatDialog {

    Q_OBJECT
protected:
    ChatDlg(const Jid& jid, PsiAccount* account, TabManager* tabManager,
            HTMLThemeManager* themeManager, IconServer* iconServer);
    virtual void init();

public:
    static ChatDlg* create(const Jid& jid, PsiAccount* account, TabManager* tabManager,
                           HTMLThemeManager* themeManager, IconServer* iconServer);
    ~ChatDlg();

    // reimplemented
    void setJid(const Jid &);
    const QString & getDisplayName();

    static QSize defaultSize();

    // reimplemented
    virtual bool readyToHide();
    virtual TabbableWidget::State state() const;
    virtual int unreadMessageCount() const;
    virtual QString desiredCaption() const;
    virtual void ensureTabbedCorrectly();

public:
    PsiAccount* account() const;

signals:
    void aInfo(const Jid &);
    void aHistory(const Jid &);
    void aVoice(const Jid &);
    void messagesRead(const Jid &);
    void aSend(const Message &);
    void aFile(const Jid &);

    /**
     * Signals if user (re)started/stopped composing
     */
    void composing(bool);

protected:
    virtual void setShortcuts();

    // reimplemented
    void closeEvent(QCloseEvent *);
    void resizeEvent(QResizeEvent *);
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void dropEvent(QDropEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    bool eventFilter(QObject *obj, QEvent *event);

    public
slots:
    // reimplemented
    virtual void deactivated();
    virtual void activated();

    virtual void optionsUpdate();
    void updateContact(const Jid &, bool);

    /** Creates MoodChatEvent for \param jid 's \param mood change (if needed) */
    void moodPublished(const Mood& mood, const Jid& jid);

    /** Creates TuneChatEvent for \param jid (if needed) */
    void tunePublished(const Tune& mood, const Jid& jid);

    /**
     * Creates FileTrasferChatEvent::incoming
     * \param fileName indicates incoming file name 
     */
    void incomingFileTransfer(const QString& fileName);

    /**
     * Creates FileTrasferChatEvent::rejected
     * \param fileName indicates rejected file name 
     */
    void rejectedFileTransfer(const QString& fileName);

    void incomingMessage(const Message &);

    /** Updates avatar label and IconServer with \param j's avatar */
    virtual void updateAvatar(const Jid& j) = 0;

    protected
slots:
    void doInfo();
    virtual void doHistory();
    void doSend();
    void doVoice();
    void doFile();

    private
slots:
    void setKeepOpenFalse();
    void setWarnSendFalse();
    virtual void updatePGP();
    virtual void setPGPEnabled(bool enabled);
    void encryptedMessageSent(int, bool, int, const QString &);
    void slotScroll();
    void setChatState(XMPP::ChatState s);
    void updateIsComposing(bool);
    void setContactChatState(ChatState s);
    void capsChanged(const Jid&);
    void addEmoticon(QString text);
    void initComposing();
    void setComposing();

    protected
slots:
    void checkComposing();

protected:


    // reimplemented
    virtual void invalidateTab();

    void resetComposing();
    void doneSend();
    virtual void setLooks();
    void setSelfDestruct(int);
    void deferredScroll();

    virtual void chatEditCreated();

    struct UserStatus {
        UserStatus() : userListItem(0), statusType(XMPP::Status::Offline) {}
        
        UserListItem* userListItem;
        XMPP::Status::Type statusType;
        QString status;
        QString publicKeyID;
    };
    
    UserStatus userStatusFor(const Jid& jid, QList<UserListItem*> ul, bool forceEmptyResource);

    enum SpooledType {

        Spooled_None,
        Spooled_OfflineStorage
    };

    virtual void initUi() = 0;
    virtual void capsChanged();
    virtual void contactUpdated(UserListItem* u, int status, const QString& statusString);

    void appendMessage(const Message &, bool local = false);
    virtual bool isEncryptionEnabled() const;

    /** 
     * Appends chat event (not message nor emote event)
     */
    virtual void appendChatEvent(ChatEvent* event) = 0;
    virtual void appendEmoteMessage(SpooledType spooled, const QDateTime& time, bool local, QString txt) = 0;
    virtual void appendNormalMessage(SpooledType spooled, const QDateTime& time, bool local, QString txt) = 0;
    
    /** Appends to message body message fields (subject and URL list) */
    virtual void appendMessageFields(const Message& m, QString& messageBody) = 0;
    virtual void nicksChanged();

    /** Returns local nickname if local is true or destination nickname otherwise */
    QString whoNick(bool local) const;

    /** We pass it to MUC/Chat dialog constructor */
    HTMLThemeManager* themeManager;

    /** We pass it to MUC/Chat dialog constructor */
    IconServer* iconServer;

private:
    bool highlightersInstalled_;
    QString dispNick_;
    int status_;
    QString statusString_;

    void initActions();
    QAction* act_send_;
    QAction* act_scrollup_;
    QAction* act_scrolldown_;
    QAction* act_close_;

    int pending_;
    bool keepOpen_;
    bool warnSend_;

    QTimer* selfDestruct_;

    QString key_;
    int transid_;
    Message m_;
    bool lastWasEncrypted_;

    // Message Events & Chat States
    QTimer* composingTimer_;
    bool isComposing_;
    bool sendComposingEvents_;
    QString eventId_;
    ChatState contactChatState_;
    ChatState lastChatState_;
};

#endif
