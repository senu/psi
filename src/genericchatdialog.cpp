#include "genericchatdialog.h"
#include "xmpp_htmlelement.h"
#include "psioptions.h"
#include "common.h"
#include "textutil.h"
#include "esystemchatevent.h"

class GenericChatDialog;


GenericChatDialog::GenericChatDialog()
: textFormatter_(false, true, false), findDialog(0) {

    gcObject = new GenericChatDialogQObject(this);

}


GenericChatDialog::~GenericChatDialog() {
    delete gcObject;
}
static const QString me_cmd = "/me ";


QString GenericChatDialog::messageText(const XMPP::Message& m) {

    bool emote = isEmoteMessage(m),
        modified;

    QString txt;

    qDebug() << "message text containsHTML" << m.containsHTML() << m.body() << m.html().toString("notb3") << "EOF";

    if (m.containsHTML() && PsiOptions::instance()->getOption("options.html.chat.render").toBool() && !m.html().text().isEmpty()) {
        txt = m.html().toString("span"); //TODO + 23 remove /me if emote
    }
    else {
        if (emote) {
            txt = "<span>" + m.body().mid(me_cmd.length()) + "</span>";
        }
        else {
            txt = TextUtil::plain2rich(m.body()); //plain2rich returns everything wrapped with <span/>
        }
    }

    qDebug() << "messageText1.5" << txt;

    textFormatter_.setDoEmoticonify(PsiOptions::instance()->getOption("options.ui.emoticons.use-emoticons").toBool());
    textFormatter_.setDoLegacyFormatting(PsiOptions::instance()->getOption("options.ui.chat.legacy-formatting").toBool());

    txt = messageValidator_.validateMessage(txt, &modified, &textFormatter_);

    qDebug() << "messageText2" << txt;
    return txt;
}


bool GenericChatDialog::isEmoteMessage(const XMPP::Message& m) {
    if (m.body().startsWith(me_cmd) || m.html().text().trimmed().startsWith(me_cmd)) {
        return true;
    }

    return false;
}


bool GenericChatDialog::doConsecutiveMessage(const QDateTime& time, bool local) {
    //Q_ASSERT(time >= lastMsgTime); this is not true for offline messages

    if (lastMsgTime.secsTo(time) > 3 * 60) { //too old
        return false;
    }

    if ((local && lastEventOwner == Outgoing) || (!local && lastEventOwner == Incoming)) { //from the same user
        return true;
    }

    return false;
}


void GenericChatDialog::updateLastMsgTimeAndOwner(const QDateTime& t, LastEventOwner owner) {
    lastEventOwner = owner;

    if (t.date() != lastMsgTime.date()) { //date changed event
        chatView()->appendEvent(new ExtendedSystemChatEvent(QObject::tr("Date changed: %1").arg(t.date().toString(Qt::ISODate))));
        lastEventOwner = Other;
    }

    lastMsgTime = t;
}


StatusChatEvent::StatusEventType GenericChatDialog::statusToChatViewStatus(int status) const {

    switch (status) {
        case STATUS_OFFLINE: return StatusChatEvent::Offline;
        case STATUS_AWAY: return StatusChatEvent::Away;
        case STATUS_XA: return StatusChatEvent::Xa;
        case STATUS_DND: return StatusChatEvent::Dnd;
        case STATUS_CHAT: return StatusChatEvent::Chat;
        case STATUS_INVISIBLE: return StatusChatEvent::Invisible;
        case STATUS_ONLINE:
        default: return StatusChatEvent::Online;
    }
}


void GenericChatDialog::openFindGC(QWidget* chatDialogWidget) {
    if (findDialog)
        ::bringToFront(findDialog);
    else {
        findDialog = new FindDialog(lastSearch, chatDialogWidget);
        findDialog->show();
    }
}


void GenericChatDialog::doFindGC(const QString &str) {
    lastSearch = str;
    if (chatView()->internalFind(str)) {
        findDialog->found();
    }
    else {
        findDialog->error(str);
    }
}


void GenericChatDialog::logSelectionChanged() {
#ifdef Q_WS_MAC
    if (chatView()->hasSelectedText()) {
        chatView()->setFocus();
    }
    else {
        chatEdit()->setFocus();
    }
#endif
}

bool GenericChatDialog::handleCopyEvent(QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *e = (QKeyEvent *) event;
        if ((e->key() == Qt::Key_C && (e->modifiers() & Qt::ControlModifier)) ||
            (e->key() == Qt::Key_Insert && (e->modifiers() & Qt::ControlModifier))) {
            if (!chatEdit()->textCursor().hasSelection()) {
                chatView()->copySelectedText();
                return true;
            }
        }
    }

    return false;
}

void GenericChatDialogQObject::logSelectionChanged() {
    dlg->logSelectionChanged();
}


void GenericChatDialogQObject::chatViewCreated() {
#ifdef Q_WS_MAC
    connect(dlg->chatView(), SIGNAL(selectionChanged()), this, SLOT(logSelectionChanged()));
#endif
}

