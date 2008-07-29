#include <QHash>
#include "userchatevent.h"


void UserChatData::setNick(QString nick) {
    nick_ = nick;
}


QString UserChatData::nick() const {
    return nick_;
}


void UserChatData::setJid(QString jid) {
    jid_ = jid;
}


QString UserChatData::jid() const {
    return jid_;
}


QString UserChatData::service() const {
    return service_;
}


void UserChatData::setService(QString service) {
    service_ = service;
}


void UserChatData::setUserIconPath(QString userIconPath) {
    userIconPath_ = userIconPath;
}


QString UserChatData::userIconPath()const {
    return userIconPath_;
}


QString UserChatData::userStatusIcon() const {
    return userStatusIcon_;
}


void UserChatData::setUserStatusIcon(QString userStatusIcon) {
    userStatusIcon_ = userStatusIcon;
}


void UserChatData::setLocal(bool is) {
    isLocal_ = is;
}


bool UserChatData::isLocal() const {
    return isLocal_;
}


void UserChatData::setSpooled(bool is) {
    isSpooled_ = is;
}


bool UserChatData::isSpooled() const {
    return isSpooled_;
}

QColor UserChatData::userColor() const {
    if(userColor_.isValid()) {
        return userColor_;
    }
    else {
        return QColor("pink");
    }
}

void UserChatData::setUserColor(const QColor& color) {
    userColor_ = color;
}
