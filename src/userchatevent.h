#ifndef USEREVENT_H_
#define	USEREVENT_H_

#include <QString>
#include <QColor>
#include "chatEvent.h"

//TODO rename file


/**
 * Contains ChatEvent sender information (nick,jid,icon, ...) 
 *   
 * For message and user-oriented events  
 */
class UserChatData {

public:

    QString jid() const;
    QString nick() const;
    QString userIconPath() const;
    QString service() const;

    /** Is it our message? */
    bool isLocal() const;

    /** Offline storage */ //TODO enum/ better name
    bool isSpooled() const;

    void setJid(QString);
    void setNick(QString);
    void setUserIconPath(QString);
    void setService(QString);
    void setLocal(bool);
    void setSpooled(bool);


    /** Returns userStatusIcon */
    QString userStatusIcon() const;

    /** Sets userStatusIcon */
    void setUserStatusIcon(QString userStatusIcon);


    /**
     * Returns userColor.
     * 
     * It's used for MUC nick coloring.
     */
    QColor userColor() const;

    /** Sets userColor */
    void setUserColor(const QColor& userColor);


private:
    QString nick_;
    QString jid_;
    QString service_;
    QString userIconPath_;
    QString userStatusIcon_;

    bool isSpooled_;
    bool isLocal_;

    QColor userColor_;

};

#endif	

