#ifndef _PLAINTEXTCHATTHEME_H
#define	_PLAINTEXTCHATTHEME_H

#include <Qt>
#include <QDir>
#include <QString>
#include <QFont>
#include <QColor>

#include "chatTheme.h"

#include "fileTransferChatEvent.h"
#include "statusChatEvent.h"
#include "messagechatevent.h"
#include "emotechatevent.h"
#include "systemchatevent.h"
#include "moodchatevent.h"
#include "tunechatevent.h"

class ChatTheme;
class FileTransferChatEvent;
class StatusChatEvent;
class MessageChatEvent;
class ChatEvent;


/** ChatTheme used by PlainTextChatView */
class PlainTextChatTheme : public ChatTheme {

    //...	
public:

    PlainTextChatTheme();

    QString createIncomingMessagePart(const MessageChatEvent* event) const;
    QString createOutgoingMessagePart(const MessageChatEvent* event) const;

    QString createFileTransferEventPart(const FileTransferChatEvent* event) const;
    QString createStatusEventPart(const StatusChatEvent* event) const;

    QString createEmoteEventPart(const EmoteChatEvent* event) const;
    QString createMoodEventPart(const MoodChatEvent* event) const;
    QString createTuneEventPart(const TuneChatEvent* event) const;
    QString createSystemEventPart(const SystemChatEvent* event) const;

    /** Always returns true */
    bool isValid();

    //options accessors

    /** Returns chatFont */
    QFont chatFont() const;

    /** Sets chatFont */
    void setChatFont(const QFont& chatFont);

    /** Returns incomingNickColor */
    QString incomingNickColor() const;

    /** Sets incomingNickColor */
    void setIncomingNickColor(const QString& incomingNickColor);

    /** Returns outgoingNickColor */
    QString outgoingNickColor() const;

    /** Sets outgoingNickColor */
    void setOutgoingNickColor(const QString& outgoingNickColor);

    /** Returns spooledNickColor */
    QString spooledNickColor() const;

    /** Sets spooledNickColor */
    void setSpooledNickColor(const QString& spooledNickColor);

    /** Returns systemMessageColor */
    QString systemMessageColor() const;

    /** Sets systemMessageColor */
    void setSystemMessageColor(const QString& systemMessageColor);
    
    /** Returns useChatSaysStyle */
    bool useChatSaysStyle() const;

    /** Sets useChatSaysStyle */
    void setUseChatSaysStyle(bool useChatSaysStyle);

private:
    /** Creates time string */
    QString formatTimeStamp(const QDateTime &time) const;

    /** Returns color name based on message type*/
    QString colorString(bool local, bool isSpooled) const; //TODO ? 74 make it customizable


    //Theme options from PsiOptions

    /** Font used to display chat events and messages */
    QFont chatFont_;

    /** Nick color (incoming message) */
    QString incomingNickColor_;

    /** Nick color (outgoing message) */
    QString outgoingNickColor_;

    /** Nick color (spooled message) */
    QString spooledNickColor_;

    /** Color of system/status/emote/filetransfer event */
    QString systemMessageColor_;

    /**
     * If false, message will look like:
     *   <nick> hello 
     * otherwise:
     *   nick says: hello
     */
    bool useChatSaysStyle_;


};

#endif

