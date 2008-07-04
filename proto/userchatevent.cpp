#include "userchatevent.h"


void UserChatEvent::setNick(QString nick) {
    _nick = nick;
}


QString UserChatEvent::nick() const {
    return _nick;
}


void UserChatEvent::setJid(QString jid) {
    _jid = jid;
}


QString UserChatEvent::jid() const {
    return _jid;
}


QString UserChatEvent::service() const {
    return _service;
}


void UserChatEvent::setService(QString service) {
    _service = service;
}


void UserChatEvent::setUserIconPath(QString userIconPath) {
    _userIconPath = userIconPath;
}


QString UserChatEvent::userIconPath()const {
    return _userIconPath;
}


QString UserChatEvent::userStatusIcon() const {
    return _userStatusIcon;
}


void UserChatEvent::setUserStatusIcon(QString userStatusIcon) {
    _userStatusIcon = userStatusIcon;
}


int UserChatEvent::userHash() const {
    return _jid.length() > 0 ? _jid[0].unicode() : 700; //TODO best hash function you ever seen
}
