#ifndef _TUNECHATEVENT_H
#define	_TUNECHATEVENT_H

#include <Qt>
#include <QString>

#include "userchatdata.h"
#include "chatTheme.h"

class ChatTheme;
class AstractChatEvent;

//TODO - 90 talk with David Smith - i would like to have separate template for tune/mood with jid, etc

/** Tune [XEP-0118] ChatEvent */
class TuneChatEvent : public ChatEvent, public UserChatData {

public:

    /** Sets \param artist and \param title*/
    TuneChatEvent(const QString& artist, const QString& title);

    /** Returns title */
    QString title() const;

    /** Sets title */
    void setTitle(const QString& title);

    /** Returns artist */
    QString artist() const;

    /** Sets artist */
    void setArtist(const QString& artist);

    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

private:
    /** Artist of song */
    QString artist_;

    /** Song title */
    QString title_;
};


#endif

