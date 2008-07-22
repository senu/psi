#ifndef _USEREVENT_H
#define	_USEREVENT_H

#include <QString>
#include "chatEvent.h"

//TODO rename file

/**
 * Contains ChatEvent sender information (nick,jid,icon, ...) 
 *   
 * For message and user-oriented events  
 */
class UserChatData  {
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

    /** Returns userHash */
    virtual uint userHash() const;


private:
    QString _nick;
    QString _jid;
    QString _service;
    QString _userIconPath;
    QString _userStatusIcon;

    bool _isSpooled;
    bool _isLocal;

};

#endif	

