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
    /** Reads theme from filesystem */
    //    PlainTextChatTheme(QString path); //TODO 73 theme options from psi options passed here

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
    
private:
    /** Creates time string */
    QString formatTimeStamp(const QDateTime &time) const;

    /** Returns color name based on message type*/
    QString colorString(bool local, bool isSpooled) const; //TODO ? 74 make it customizable


    //Theme options from PsiOptions
    
    /** Font used to display chat events and messages */
    QFont chatFont;
    
    /** Nick color (incoming message) */
    QColor incomingNickColor;
    
    /** Nick color (outgoing message) */
    QColor outgoingNickColor;
    
    /** Nick color (spooled message) */
    QColor spooledNickColor;
    
    /** Color of system/status/emote/filetransfer event */
    QColor systemMessageColor;

    /**
     * If false, message will look like:
     *   <nick> hello 
     * otherwise:
     *   nick says: hello
     */
    bool useChatSaysStyle;

    
};

#endif

