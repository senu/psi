
#include "abstractChatEvent.h"

#include "psichatdlg.h"

#include <QLabel>
#include <QCursor>
#include <QLineEdit>
#include <QToolButton>
#include <QLayout>
#include <QSplitter>
#include <QToolBar>
#include <QPixmap>
#include <QColor>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QResizeEvent>
#include <QMenu>
#include <QDragEnterEvent>
#include <QMessageBox>

#include "psicon.h"
#include "psiaccount.h"
#include "iconaction.h"
#include "stretchwidget.h"
#include "psiiconset.h"
#include "iconwidget.h"
#include "fancylabel.h"
#include "msgmle.h"
#include "iconselect.h"
#include "avatars.h"
#include "psitooltip.h"
#include "psioptions.h"
#include "shortcutmanager.h"
#include "accountlabel.h"
#include "iconlabel.h"
#include "capsmanager.h"
#include "psicontactlist.h"
#include "userlist.h"
#include "jidutil.h"
#include "textutil.h"

#include "emotechatevent.h"
#include "messagechatevent.h"
#include "systemchatevent.h"
#include "esystemchatevent.h"


PsiChatDlg::PsiChatDlg(const Jid& jid, PsiAccount* pa, TabManager* tabManager, 
                       HTMLThemeManager* themeManager, IconServer* iconServer)
: ChatDlg(jid, pa, tabManager, themeManager, iconServer) 
{
    connect(account()->psi(), SIGNAL(accountCountChanged()), this, SLOT(updateIdentityVisibility()));
}


void PsiChatDlg::initUi() {
    ui_.setupUi(this);
    ui_.lb_ident->setAccount(account());
    ui_.lb_ident->setShowJid(false);

    PsiToolTip::install(ui_.lb_status);
    ui_.lb_status->setPsiIcon(IconsetFactory::iconPtr("status/noauth"));

    ui_.tb_emoticons->setIcon(IconsetFactory::icon("psi/smile").icon());

    ChatTheme::ChatInfo chatInfo;

    UserListItem *ui = account()->findFirstRelevant(jid()); //TODO ask kev (relevant)
    QString destNick(JIDUtil::nickOrJid(ui->name(), jid().full())); //TODO

    //TODO iss| getDisplayName() doesnt work
    chatInfo.chatName = destNick;
    chatInfo.destinationName = destNick;
    chatInfo.destinationDisplayName = jid().full();
    chatInfo.sourceName = account()->nick();
    chatInfo.incomingIconPath = "icon://avatars/"+jid().full()+".png"; //TODO
    chatInfo.outgoingIconPath = "icon://avatars/"+account()->jid().full()+".png";
    chatInfo.timeOpened = QDateTime::currentDateTime();

    lastMsgTime = QDateTime::currentDateTime();
    lastEventOwner = Other;
    
    ui_.log->init(chatInfo, themeManager, iconServer);

    connect(ui_.mle, SIGNAL(textEditCreated(QTextEdit*)), SLOT(chatEditCreated()));
    chatEditCreated();

#ifdef Q_WS_MAC
    connect(chatView(), SIGNAL(selectionChanged()), SLOT(logSelectionChanged())); //TODO
#endif

    initToolButtons();
    initToolBar();
    updateAvatar(jid());
    updateAvatar(account()->jid());

    PsiToolTip::install(ui_.avatar);

    UserListItem* u = account()->findFirstRelevant(jid());
    if (u && u->isSecure(jid().resource())) {
        setPGPEnabled(true);
    }

    connect(account()->avatarFactory(), SIGNAL(avatarChanged(const Jid&)), this, SLOT(updateAvatar(const Jid&)));

    pm_settings_ = new QMenu(this);
    connect(pm_settings_, SIGNAL(aboutToShow()), SLOT(buildMenu()));
    ui_.tb_actions->setMenu(pm_settings_);

    connect(account()->capsManager(), SIGNAL(capsChanged(const Jid&)), SLOT(capsChanged(const Jid&)));

    QList<int> list;
    list << 324;
    list << 96;
    ui_.splitter->setSizes(list);

    smallChat_ = PsiOptions::instance()->getOption("options.ui.chat.use-small-chats").toBool();
}


void PsiChatDlg::updateCountVisibility() {
    if (PsiOptions::instance()->getOption("options.ui.message.show-character-count").toBool() && !smallChat_) {
        ui_.lb_count->show();
    }
    else {
        ui_.lb_count->hide();
    }
}


void PsiChatDlg::setLooks() {
    ChatDlg::setLooks();

    ui_.splitter->optionsChanged();
    ui_.mle->optionsChanged();

    ui_.tb_pgp->hide();
    if (smallChat_) {
        ui_.lb_status->hide();
        ui_.le_jid->hide();
        ui_.tb_actions->hide();
        ui_.tb_emoticons->hide();
        ui_.toolbar->hide();
    }
    else {
        ui_.lb_status->show();
        ui_.le_jid->show();
        if (PsiOptions::instance()->getOption("options.ui.chat.central-toolbar").toBool()) {
            ui_.toolbar->show();
            ui_.tb_actions->hide();
            ui_.tb_emoticons->hide();
        }
        else {
            ui_.toolbar->hide();
            ui_.tb_emoticons->setVisible(PsiOptions::instance()->getOption("options.ui.emoticons.use-emoticons").toBool());
            ui_.tb_actions->show();
        }
    }

    updateIdentityVisibility();
    updateCountVisibility();

    // toolbuttons
    QIcon i;
    i.setPixmap(IconsetFactory::icon("psi/cryptoNo").impix(), QIcon::Automatic, QIcon::Normal, QIcon::Off);
    i.setPixmap(IconsetFactory::icon("psi/cryptoYes").impix(), QIcon::Automatic, QIcon::Normal, QIcon::On);
    act_pgp_->setPsiIcon(0);
    act_pgp_->setIcon(i);
}


void PsiChatDlg::setShortcuts() {
    ChatDlg::setShortcuts();

    act_clear_->setShortcuts(ShortcutManager::instance()->shortcuts("chat.clear"));
    act_info_->setShortcuts(ShortcutManager::instance()->shortcuts("common.user-info"));
    act_history_->setShortcuts(ShortcutManager::instance()->shortcuts("common.history"));
}


void PsiChatDlg::updateIdentityVisibility() {
    if (!smallChat_) {
        bool visible = account()->psi()->contactList()->enabledAccounts().count() > 1;
        ui_.lb_ident->setVisible(visible);
    }
    else {
        ui_.lb_ident->setVisible(false);
    }
}


void PsiChatDlg::initToolButtons() {
    act_clear_ = new IconAction(tr("Clear chat window"), "psi/clearChat", tr("Clear chat window"), 0, this);
    connect(act_clear_, SIGNAL(activated()), SLOT(doClearButton()));

    connect(account()->psi()->iconSelectPopup(), SIGNAL(textSelected(QString)), this, SLOT(addEmoticon(QString)));
    act_icon_ = new IconAction(tr("Select icon"), "psi/smile", tr("Select icon"), 0, this);
    act_icon_->setMenu(account()->psi()->iconSelectPopup());
    ui_.tb_emoticons->setMenu(account()->psi()->iconSelectPopup());

    act_voice_ = new IconAction(tr("Voice Call"), "psi/voice", tr("Voice Call"), 0, this);
    connect(act_voice_, SIGNAL(activated()), SLOT(doVoice()));
    act_voice_->setEnabled(false);

    act_file_ = new IconAction(tr("Send file"), "psi/upload", tr("Send file"), 0, this);
    connect(act_file_, SIGNAL(activated()), SLOT(doFile()));

    act_pgp_ = new IconAction(tr("Toggle encryption"), "psi/cryptoNo", tr("Toggle encryption"), 0, this, 0, true);
    ui_.tb_pgp->setDefaultAction(act_pgp_);

    act_info_ = new IconAction(tr("User info"), "psi/vCard", tr("User info"), 0, this);
    connect(act_info_, SIGNAL(activated()), SLOT(doInfo()));

    act_history_ = new IconAction(tr("Message history"), "psi/history", tr("Message history"), 0, this);
    connect(act_history_, SIGNAL(activated()), SLOT(doHistory()));

    act_compact_ = new IconAction(tr("Toggle Compact/Full size"), "psi/compact", tr("Toggle Compact/Full size"), 0, this);
    connect(act_compact_, SIGNAL(activated()), SLOT(toggleSmallChat()));
}


void PsiChatDlg::initToolBar() {
    ui_.toolbar->setWindowTitle(tr("Chat toolbar"));
    ui_.toolbar->setIconSize(QSize(16, 16));
    ui_.toolbar->addAction(act_clear_);
    ui_.toolbar->addWidget(new StretchWidget(ui_.toolbar));
    ui_.toolbar->addAction(act_icon_);
    ui_.toolbar->addAction(act_file_);
    if (PsiOptions::instance()->getOption("options.pgp.enable").toBool()) {
        ui_.toolbar->addAction(act_pgp_);
    }
    ui_.toolbar->addAction(act_info_);
    ui_.toolbar->addAction(act_history_);
    if (account()->voiceCaller()) {
        ui_.toolbar->addAction(act_voice_);
    }
}


void PsiChatDlg::contextMenuEvent(QContextMenuEvent *) {
    pm_settings_->exec(QCursor::pos());
}


void PsiChatDlg::capsChanged() {
    ChatDlg::capsChanged();

    QString resource = jid().resource();
    UserListItem *ul = account()->findFirstRelevant(jid());
    if (resource.isEmpty() && ul && !ul->userResourceList().isEmpty()) {
        resource = (*(ul->userResourceList().priority())).name();
    }
    act_voice_->setEnabled(!account()->capsManager()->isEnabled() || (ul && ul->isAvailable() && account()->capsManager()->features(jid().withResource(resource)).canVoice()));
}


void PsiChatDlg::activated() {
    ChatDlg::activated();

    updateCountVisibility();
}


void PsiChatDlg::setContactToolTip(QString text) {
    ui_.lb_status->setToolTip(text);
    ui_.avatar->setToolTip(text);
}


void PsiChatDlg::contactUpdated(UserListItem* u, int status, const QString& statusString) {
    Q_UNUSED(statusString);

    if (status == -1 || !u) {
        ui_.lb_status->setPsiIcon(IconsetFactory::iconPtr("status/noauth"));
    }
    else {
        ui_.lb_status->setPsiIcon(PsiIconset::instance()->statusPtr(jid(), status));
    }

    if (u) {
        setContactToolTip(u->makeTip(true, false));
    }
    else {
        setContactToolTip(QString());
    }

    if (u) {
        QString name;
        QString j;
        if (jid().resource().isEmpty())
            j = JIDUtil::toString(u->jid(), true);
        else
            j = JIDUtil::toString(u->jid().userHost(), false) + '/' + jid().resource();

        if (!u->name().isEmpty())
            name = u->name() + QString(" <%1>").arg(j);
        else
            name = j;

        ui_.le_jid->setText(name);
        ui_.le_jid->setCursorPosition(0);
        ui_.le_jid->setToolTip(name);
    }
}


void PsiChatDlg::updateAvatar(const Jid& j) {
  
    qDebug() << "updateAvatar" << j.full();
    //ignore avatars other than our or destination avatars
    if (!j.compare(jid(), false) && !j.compare(account()->jid(), false)) {
        return;
    }
    qDebug() << "updateAvatar" << j.full();
    
    QString res;
    QString client;

    if (!PsiOptions::instance()->getOption("options.ui.chat.avatars.show").toBool()) {
        ui_.avatar->hide();
        return;
    }
//TODO AAAA
    UserListItem *ul = account()->findFirstRelevant(j);
    if (ul && !ul->userResourceList().isEmpty()) {
        UserResourceList::Iterator it = ul->userResourceList().find(j.resource());
        if (it == ul->userResourceList().end())
            it = ul->userResourceList().priority();

        res = (*it).name();
        client = (*it).clientName();
    }
    //QPixmap p = account()->avatarFactory()->getAvatar(jid().withResource(res),client);
    QPixmap p = account()->avatarFactory()->getAvatar(j.withResource(res));
    if (p.isNull()) {
        ui_.avatar->hide();
    }
    else {
        int size = PsiOptions::instance()->getOption("options.ui.chat.avatars.size").toInt();
        ui_.avatar->setPixmap(p.scaled(QSize(size, size), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui_.avatar->show();

        //update avatar in IconServer (webkit chats)
        iconServer->registerIcon("avatars/"+j.full()+".png", IconServer::pixmapToPng(p));
    }
}


void PsiChatDlg::optionsUpdate() {
    smallChat_ = PsiOptions::instance()->getOption("options.ui.chat.use-small-chats").toBool();

    ChatDlg::optionsUpdate();
}


void PsiChatDlg::updatePGP() {
    if (account()->hasPGP()) {
        act_pgp_->setEnabled(true);
    }
    else {
        act_pgp_->setChecked(false);
        act_pgp_->setEnabled(false);
    }

    ui_.tb_pgp->setVisible(account()->hasPGP() &&
                           !smallChat_ &&
                           !PsiOptions::instance()->getOption("options.ui.chat.central-toolbar").toBool());
}


void PsiChatDlg::doClearButton() {
    int n = QMessageBox::information(this, tr("Warning"), tr("Are you sure you want to clear the chat window?\n(note: does not affect saved history)"), tr("&Yes"), tr("&No"));
    if (n == 0)
        doClear();
}


void PsiChatDlg::setPGPEnabled(bool enabled) {
    act_pgp_->setChecked(enabled);
}


void PsiChatDlg::toggleSmallChat() {
    smallChat_ = !smallChat_;
    setLooks();
}


void PsiChatDlg::buildMenu() {
    // Dialog menu
    pm_settings_->clear();
    pm_settings_->addAction(act_compact_);
    pm_settings_->addAction(act_clear_);
    pm_settings_->insertSeparator();

    pm_settings_->addAction(act_icon_);
    pm_settings_->addAction(act_file_);
    if (account()->voiceCaller())
        act_voice_->addTo(pm_settings_);
    pm_settings_->addAction(act_pgp_);
    pm_settings_->insertSeparator();

    pm_settings_->addAction(act_info_);
    pm_settings_->addAction(act_history_);
}


void PsiChatDlg::updateCounter() {
    ui_.lb_count->setNum(chatEdit()->text().length());
}


void PsiChatDlg::appendEmoteMessage(SpooledType spooled, const QDateTime& time, bool local, QString txt) {

    EmoteChatEvent * ev = new EmoteChatEvent(); //ev will be freed in ChatView
    //    ev->setJid(whoNick(local)); //TODO
    ev->setNick(whoNick(local));
    ev->setTimeStamp(time);
    ev->setLocal(local);
    ev->setSpooled(spooled);
    ev->setService("Jabber");
    ev->setMessage(txt); //TODO escape?

    chatView()->appendEvent(ev);
    updateLastMsgTimeAndOwner(time, Other);
}


void PsiChatDlg::appendNormalMessage(SpooledType spooled, const QDateTime& time, bool local, QString txt) {

    MessageChatEvent * msg = new MessageChatEvent(); //will be created in another place, of course

    msg->setNick(whoNick(local));
    msg->setTimeStamp(time);
    msg->setLocal(local);
    msg->setConsecutive(doConsecutiveMessage(time, local));
    msg->setSpooled(spooled);
    msg->setService("Jabber");
    msg->setBody(txt); //TODO escape?

    chatView()->appendMessage(msg);
    updateLastMsgTimeAndOwner(time, local ? Outgoing : Incoming);
}


void PsiChatDlg::appendChatEvent(const ChatEvent* event) {
    chatView()->appendEvent(event);
    updateLastMsgTimeAndOwner(event->timeStamp(), Other);
}

/*
void PsiChatDlg::appendSystemMsg(const QString &str) {
    QDateTime time = QDateTime::currentDateTime();

    ExtendedSystemChatEvent * ev = new ExtendedSystemChatEvent(str);
    ev->setType(SystemChatEvent::Other);
    ev->setTimeStamp(time);

    appendSystemMsg(ev);
}
*/

void PsiChatDlg::appendMessageFields(const Message& m) {
    //TODO vw rf

    /*
    if (!m.subject().isEmpty()) {
        chatView()->appendText(QString("<b>") + tr("Subject:") + "</b> " + QString("%1").arg(Qt::escape(m.subject())));
    }
    if (!m.urlList().isEmpty()) {
        UrlList urls = m.urlList();
        chatView()->appendText(QString("<i>") + tr("-- Attached URL(s) --") + "</i>");
        for (QList<Url>::ConstIterator it = urls.begin(); it != urls.end(); ++it) {
            const Url &u = *it;
            chatView()->appendText(QString("<b>") + tr("URL:") + "</b> " + QString("%1").arg(TextUtil::linkify(Qt::escape(u.url()))));
            chatView()->appendText(QString("<b>") + tr("Desc:") + "</b> " + QString("%1").arg(u.desc()));
        }
    }
     */

}


bool PsiChatDlg::isEncryptionEnabled() const {
    return act_pgp_->isChecked();
}


QString PsiChatDlg::colorString(bool local, ChatDlg::SpooledType spooled) const {
    if (spooled == ChatDlg::Spooled_OfflineStorage)
        return "#008000";

    if (local)
        return "#FF0000";

    return "#0000FF";
}


ChatView* PsiChatDlg::chatView() const {
    return ui_.log->chatView();
}


ChatEdit* PsiChatDlg::chatEdit() const {
    return ui_.mle->chatEdit();
}


void PsiChatDlg::chatEditCreated() {
    ChatDlg::chatEditCreated();

    connect(chatEdit(), SIGNAL(textChanged()), this, SLOT(updateCounter()));
    chatEdit()->installEventFilter(this);
}

QString PsiChatDlg::messageText(const XMPP::Message& m) {
    return GenericChatDialog::messageTextGC(m);
}

bool PsiChatDlg::isEmoteMessage(const XMPP::Message& m) {
    return GenericChatDialog::isEmoteMessageGC(m);
}

StatusChatEvent::StatusEventType PsiChatDlg::statusToChatViewStatus(int status) const {
    return GenericChatDialog::statusToChatViewStatus(status);
}