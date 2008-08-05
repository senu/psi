#ifndef _MOODCHATEVENT_H
#define	_MOODCHATEVENT_H

#include <Qt>
#include <QString>

#include "chatEvent.h"
#include "chatTheme.h"
#include "userchatdata.h"

class ChatTheme;
class AstractChatEvent;


/** Mood [XEP-0107] ChatEvent */
class MoodChatEvent : public ChatEvent, public UserChatData {

public:


    /** Sets \param type and \param text*/
    MoodChatEvent(const QString& type, const QString& text)
    : ChatEvent(), type_(type), text_(text) {
    }

    /** Returns text */
    QString text() const;

    /** Sets text */
    void setText(const QString& text);

    /** Returns type */
    QString type() const;

    /** Sets type */
    void setType(const QString& type);

    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

private:
    /** Type of mood (excited, proud, etc)*/
    QString type_;

    /** Mood text (eg curse my nurse!) */
    QString text_;
};


#endif

