/*
 * groupchatdlg.h - dialogs for handling groupchat
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

#ifndef GROUPCHATDLG_H
#define GROUPCHATDLG_H

#include <QWidget>
#include <QDialog>


#include "advwidget.h"
#include "tabbablewidget.h"

#include "ui_groupchatdlg.h"
#include "mucmanager.h"
#include "htmlthememanager.h"
#include "iconserver.h"
#include "advwidget.h"
#include "genericchatdialog.h"

using namespace XMPP;

class PsiCon;
class PsiAccount;
class PsiOptions;
class QRect;
class GCMainDlg;
class QPainter;
class QColorGroup;
class Q3DragObject;
namespace XMPP {
    class Message;
}


/*class GCLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    GCLineEdit(QWidget *parent=0, const char *name=0);

signals:
    void upPressed();
    void downPressed();

protected:
    void keyPressEvent(QKeyEvent *);
};*/

class GCMainDlg : public TabbableWidget, public GenericChatDialog {

    Q_OBJECT
public:
    GCMainDlg(PsiAccount *, const Jid &, TabManager *tabManager, 
              HTMLThemeManager* themeManager, IconServer* iconServer);

    ~GCMainDlg();

    PsiAccount* account() const;

    void error(int, const QString &);
    void presence(const QString &, const Status &);
    void message(const Message &);
    void joined();
    void setPassword(const QString&);
    const QString& nick() const;

    // reimplemented
    virtual TabbableWidget::State state() const;
    virtual int unreadMessageCount() const;
    virtual QString desiredCaption() const;

protected:
    void setShortcuts();

    // reimplemented
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void closeEvent(QCloseEvent *);
    void resizeEvent(QResizeEvent*);
    void mucInfoDialog(const QString& title, const QString& message, const Jid& actor, const QString& reason);
    
    /** Returns dialog's ChatView */
    ChatView* chatView() const;
    
    /** Returns dialog's ChatEdit */
    ChatEdit* chatEdit() const;

signals:
    void aSend(const Message &);

    public 
slots:
    // reimplemented
    virtual void deactivated();
    virtual void activated();
    virtual void ensureTabbedCorrectly();

    void optionsUpdate();

    private 
slots:
    void chatEdit_returnPressed();
    void doTopic();
    
    void configureRoom();
    void pa_updatedActivity();
    void goDisc();
    void goConn();
    void lv_action(const QString &, const Status &, int);
    void buildMenu();
    void setConnecting();
    void unsetConnecting();
    void action_error(MUCManager::Action, int, const QString&);
    void updateIdentityVisibility();
   
    /** Calls openFindGC() (it must be slot and GeCD cannot inherit from QObject) */
    void openFind();
    
    /** Calls doFindGC() (it must be slot and GeCD cannot inherit from QObject) */
    void doFind(const QString &str);
    
#ifdef WHITEBOARDING
    void openWhiteboard();
#endif
    void chatEditCreated();

public:
    class Private;
    friend class Private;
private:
    Private *d;
    Ui::GroupChatDlg ui_;

    void doAlert();
    //void appendSystemMsg(const QString &, bool, const QDateTime &ts = QDateTime()); //TODO remove
    
    //reimplmented
    void fillEventWithUserInfo(UserChatData* userInfo, const Jid& j, bool forceLocal = false);
    DefaultHTMLTextFormatter * textFormatter();
    
    void appendMessage(const Message &, bool alert);
    void appendChatEvent(ChatEvent* event, bool alert = false);
    void setLooks();

    void contextMenuEvent(QContextMenuEvent *);

    QString getNickColor(QString);
    QMap<QString, int> nicks;
    int nicknumber;
    PsiOptions* options_;
    HTMLThemeManager* themeManager;
    IconServer* iconServer;
    
    QDateTime lastMsgTime_;
};


#endif
