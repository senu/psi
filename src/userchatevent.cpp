#include <QHash>
#include "userchatevent.h"


void UserChatData::setNick(QString nick) {
    _nick = nick;
}


QString UserChatData::nick() const {
    return _nick;
}


void UserChatData::setJid(QString jid) {
    _jid = jid;
}


QString UserChatData::jid() const {
    return _jid;
}


QString UserChatData::service() const {
    return _service;
}


void UserChatData::setService(QString service) {
    _service = service;
}


void UserChatData::setUserIconPath(QString userIconPath) {
    _userIconPath = userIconPath;
}


QString UserChatData::userIconPath()const {
    return _userIconPath;
}


QString UserChatData::userStatusIcon() const {
    return _userStatusIcon;
}


void UserChatData::setUserStatusIcon(QString userStatusIcon) {
    _userStatusIcon = userStatusIcon;
}


void UserChatData::setLocal(bool is) {
    _isLocal = is;
}


bool UserChatData::isLocal() const {
    return _isLocal;
}


void UserChatData::setSpooled(bool is) {
    _isSpooled = is;
}


bool UserChatData::isSpooled() const {
    return _isSpooled;
}

uint UserChatData::userHash() const {
    return qHash(_jid);
}
