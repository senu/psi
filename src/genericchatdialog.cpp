#include <QMessageBox>
#include "genericchatdialog.h"
#include "xmpp_htmlelement.h"
#include "xmpp_jid.h"
#include "psioptions.h"
#include "common.h"
#include "textutil.h"
#include "esystemchatevent.h"

class GenericChatDialog;
using XMPP::Jid;


GenericChatDialog::GenericChatDialog() : findDialog(0) {

    lastMsgTime = QDateTime::currentDateTime();
    lastEventOwner = Jid();
    sendXHTML = false;

    gcObject = new GenericChatDialogQObject(this);

}


GenericChatDialog::~GenericChatDialog() {
    delete gcObject;
}

static const QString me_cmd = "/me ";


QString GenericChatDialog::messageText(const XMPP::Message& m) {

    bool emote = isEmoteMessage(m),
        illformed;

    QString txt;

  //  qDebug() << "IMG messageText containsHTML" << m.containsHTML() << m.body() << m.html().toString("notb3") << "EOF";

    //reset textFormatter
    textFormatter()->setRemoveEmoteString(false);
    textFormatter()->setTextNodeNumber(0);

    if (m.containsHTML() && PsiOptions::instance()->getOption("options.html.chat.render").toBool()) {
        if (emote) {
            textFormatter()->setRemoveEmoteString(true);
        }
        txt = m.html().toString("span");
//    	qDebug() << "IMG messageText 1.3 containsHTML" << m.containsHTML() << txt << "EOF" << !m.html().text().isEmpty() << PsiOptions::instance()->getOption("options.html.chat.render").toBool();
    }
    else {
        if (emote) {
            txt = "<span>" + m.body().mid(me_cmd.length()) + "</span>";
        }
        else {
            txt = TextUtil::plain2rich(m.body());
        }
    }

    textFormatter()->setDoEmoticonify(PsiOptions::instance()->getOption("options.ui.emoticons.use-emoticons").toBool());
    textFormatter()->setDoLegacyFormatting(PsiOptions::instance()->getOption("options.ui.chat.legacy-formatting").toBool());

    txt = messageValidator_.validateMessage(txt, &illformed, textFormatter());

    if (illformed) { //html content was illformed, plain version is displayed
        textFormatter()->setTextNodeNumber(0);
        txt = messageValidator_.validateMessage(TextUtil::plain2rich(m.body()), &illformed, textFormatter());
    }

//    qDebug() << "IMG messageText 2" << txt;
    return txt;
}


bool GenericChatDialog::isEmoteMessage(const XMPP::Message& m) {
    if (m.body().startsWith(me_cmd) || m.html().text().trimmed().startsWith(me_cmd)) {
        return true;
    }

    return false;
}


bool GenericChatDialog::doConsecutiveMessage(const QDateTime& time, const Jid& sender) {
    //Q_ASSERT(time >= lastMsgTime); this is not true for offline messages

    if (lastMsgTime.secsTo(time) > 3 * 60) { //too old
        return false;
    }

    if (sender.compare(lastEventOwner, true)) {
        return true;
    }

    return false;
}


void GenericChatDialog::updateLastMsgTimeAndOwner(const QDateTime& t, const Jid& owner) {
    lastEventOwner = owner;

    if (t.date() != lastMsgTime.date()) { //date changed event
        chatView()->appendEvent(new ExtendedSystemChatEvent(QObject::tr("Date changed: %1").arg(t.date().toString(Qt::ISODate))));
        lastEventOwner = Jid();
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


void GenericChatDialogQObject::scrollUp() {
    dlg->chatView()->scrollUp();
}


void GenericChatDialogQObject::scrollDown() {
    dlg->chatView()->scrollDown();
}


void GenericChatDialogQObject::logSelectionChanged() {
    dlg->logSelectionChanged();
}


void GenericChatDialogQObject::chatViewCreated() {
#ifdef Q_WS_MAC
    connect(dlg->chatView(), SIGNAL(selectionChanged()), this, SLOT(logSelectionChanged()));
#endif
}


void GenericChatDialogQObject::doClear() {
    dlg->chatView()->clear();
    dlg->lastEventOwner = Jid();
}


void GenericChatDialogQObject::doClearButton() {
    QMessageBox::StandardButton btn = QMessageBox::information(0, tr("Warning"), tr("Are you sure you want to clear the chat window?\n(note: does not affect saved history)"), QMessageBox::Yes | QMessageBox::No);

    if (btn == QMessageBox::Yes) {
        doClear();
    }
}
