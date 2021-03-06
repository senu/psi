#ifndef PSICHATDLG_H
#define PSICHATDLG_H

#include "chatdlg.h"

#include "ui_chatdlg.h"
#include "genericchatdialog.h"

class IconAction;

class PsiChatDlg : public ChatDlg {
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
	void buildMenu();
	void updateCounter();
	void updateIdentityVisibility();
	void updateCountVisibility();

	// reimplemented
	void chatEditCreated();

    /** Calls openFindGC() (it must be slot and GeCD cannot inherit from QObject) */
    void openFind();
    
    /** Calls doFindGC() (it must be slot and GeCD cannot inherit from QObject) */
    void doFind(const QString &str);

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
    
/** Returns (null() if absent) avatar pixmap for \param j*/
    QPixmap getAvatarForJid(const Jid& j);

    //implemented
    void fillEventWithUserInfo(UserChatData* userInfo, const Jid& j, bool forceLocal = false);
    void appendChatEvent(ChatEvent* event);
    void appendMessage(SpooledType spooled, const QDateTime& time, bool local, QString txt, bool isEmote);
    
    /** Appends to message body message fields (subject and URL list) */
    void appendMessageFields(const Message& m, QString& messageBody);

    DefaultHTMLTextFormatter * textFormatter();

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
    IconAction* act_find_;

	bool smallChat_;
};

#endif
