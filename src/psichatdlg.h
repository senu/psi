#ifndef PSICHATDLG_H
#define PSICHATDLG_H

#include "chatdlg.h"

#include "ui_chatdlg.h"
#include "genericchatdialog.h"

class IconAction;

class PsiChatDlg : public ChatDlg, public GenericChatDialog
{
	Q_OBJECT
public:
	PsiChatDlg(const Jid& jid, PsiAccount* account, TabManager* tabManager, 
               HTMLThemeManager* themeManager, IconServer* iconServer);

protected:
	// reimplemented
	void contextMenuEvent(QContextMenuEvent *);

private:
	void setContactToolTip(QString text);
    

private slots:
	void toggleSmallChat();
	void doClearButton();
	void buildMenu();
	void updateCounter();
	void updateIdentityVisibility();
	void updateCountVisibility();

	// reimplemented
	void chatEditCreated();

private:

	void initToolBar();
	void initToolButtons();

	// reimplemented
	void initUi();
	void capsChanged();
	bool isEncryptionEnabled() const;
	void contactUpdated(UserListItem* u, int status, const QString& statusString);
    void updateAvatar(const Jid& j);
	void optionsUpdate();
	void updatePGP();
	void setPGPEnabled(bool enabled);
	void activated();
	void setLooks();
	void setShortcuts();
	QString colorString(bool local, SpooledType spooled) const;
    void appendChatEvent(const ChatEvent* event);
//	void appendSystemMsg(const QString &); //TODO remove
	void appendEmoteMessage(SpooledType spooled, const QDateTime& time, bool local, QString txt);
	void appendNormalMessage(SpooledType spooled, const QDateTime& time, bool local, QString txt);
	void appendMessageFields(const Message& m);

    /** Returns (null() if absent) avatar pixmap for \param j*/
    QPixmap getAvatarForJid(const Jid& j);

    /** 
     * Fills User ChatEvent with corresponding data (nick, jid, icons, etc) 
     *
     * \param userInfo will be filled 
     * \param j is jid of user owner/sender
     */
    virtual void fillEventWithUserInfo(UserChatData * userInfo, const Jid& j);
    
    //redirected
    QString messageText(const XMPP::Message& m);
    bool isEmoteMessage(const XMPP::Message& m);
    StatusChatEvent::StatusEventType statusToChatViewStatus(int status) const;
   
    //implemented

    /** Returns dialog's ChatView */
	ChatView* chatView() const;
    
    /** Returns dialog's ChatEdit */
	ChatEdit* chatEdit() const;

private:
	Ui::ChatDlg ui_;

    ChatView * _chatView;

	QMenu* pm_settings_;

	IconAction* act_clear_;
	IconAction* act_history_;
	IconAction* act_info_;
	IconAction* act_pgp_;
	IconAction* act_icon_;
	IconAction* act_file_;
	IconAction* act_compact_;
	IconAction* act_voice_;

	bool smallChat_;
};

#endif
