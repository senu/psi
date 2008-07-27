#ifndef PSICHATDLG_H
#define PSICHATDLG_H

#include "chatdlg.h"

#include "ui_chatdlg.h"

class IconAction;

class PsiChatDlg : public ChatDlg
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
    
    /** 
     * Returns true if next message should be consecutive
     * \param local indicates if it's our message 
     */
    bool doConsecutiveMessage(const QDateTime& time, bool local);

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
	void updateAvatar();
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
