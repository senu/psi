#include "genericchatdialog.h"
#include "xmpp_htmlelement.h"
#include "psioptions.h"
#include "common.h"

class GenericChatDialog;

GenericChatDialog::GenericChatDialog()
: textFormatter_(false, true, false) {

}

static const QString me_cmd = "/me ";

QString GenericChatDialog::messageTextGC(const XMPP::Message& m) {
    
    bool emote = isEmoteMessageGC(m),
        modified;
    
    QString txt;

    if (m.containsHTML() && PsiOptions::instance()->getOption("options.html.chat.render").toBool() && !m.html().text().isEmpty()) {
        txt = m.html().toString("span");
    }
    else {
        txt = "<span>" + m.body() + "</span>";
    }

    if (emote) {
        txt = txt.mid(me_cmd.length());
    }

    textFormatter_.setDoEmoticonify(PsiOptions::instance()->getOption("options.ui.emoticons.use-emoticons").toBool());
    textFormatter_.setDoLegacyFormatting(PsiOptions::instance()->getOption("options.ui.chat.legacy-formatting").toBool());

    txt = messageValidator_.validateMessage(txt, &modified, &textFormatter_);

    qDebug() << txt;
    return txt;
}


bool GenericChatDialog::isEmoteMessageGC(const XMPP::Message& m) {
    if (m.body().startsWith(me_cmd) || m.html().text().trimmed().startsWith(me_cmd)) {
        qDebug() << m.body().startsWith(me_cmd) << m.html().text().trimmed().startsWith(me_cmd);
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
        qDebug() << local << lastEventOwner;
        return true;
    }

    return false;
}

void GenericChatDialog::updateLastMsgTimeAndOwner(const QDateTime& t, LastEventOwner owner) {
    lastMsgTime = t;
    lastEventOwner = owner;

    //TODO wv remove
    /*
    bool doInsert = t.date() != lastMsgTime_.date();
    if (doInsert) {
        QString color = "#00A000";
    chatView()->appendText(QString("<font color=\"%1\">*** %2</font>").arg(color).arg(t.date().toString(Qt::ISODate)));
    }
     */
}

StatusChatEvent::StatusEventType GenericChatDialog::statusToChatViewStatus(int status) const {
    
	switch(status) {
		case STATUS_OFFLINE:    return StatusChatEvent::Offline;
        case STATUS_AWAY:       return StatusChatEvent::Away;
		case STATUS_XA:         return StatusChatEvent::Xa;
		case STATUS_DND:        return StatusChatEvent::Dnd;
		case STATUS_CHAT:       return StatusChatEvent::Chat;
		case STATUS_INVISIBLE:  return StatusChatEvent::Invisible;

		case STATUS_ONLINE:
		default:                return StatusChatEvent::Online;
	}
}