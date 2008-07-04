#ifndef _USEREVENT_H
#define	_USEREVENT_H

#include <QString>
#include "chatEvent.h"


/** Abstract ChatEvent with sender information (nick,jid,icon, ...) 
 *   
 *  For message and status events  
 */
class UserChatEvent : virtual public AbstractChatEvent { 

public:

    QString jid() const;
    QString nick() const;
    QString userIconPath() const;
    QString service() const;
    void setJid(QString);
    void setNick(QString);
    void setService(QString);
    void setUserIconPath(QString);

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

};

#endif	

