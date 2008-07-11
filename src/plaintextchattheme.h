#ifndef _PLAINTEXTCHATTHEME_H
#define	_PLAINTEXTCHATTHEME_H

#include <Qt>
#include <QDir>
#include <QString>

#include "chatTheme.h"

#include "fileTransferChatEvent.h"
#include "statusChatEvent.h"
#include "messagechatevent.h"
#include "emotechatevent.h"

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
    //    PlainTextChatTheme(QString path); //TODO theme options from psi options passed here

    QString createIncomingMessagePart(const MessageChatEvent *) const;
    QString createOutgoingMessagePart(const MessageChatEvent *) const;

    QString createFileTransferEventPart(const FileTransferChatEvent * event) const;
    QString createStatusEventPart(const StatusChatEvent * event) const;

    QString createEmoteEventPart(const EmoteChatEvent * event) const;
private:
    /** Creates time string */
    QString formatTimeStamp(const QDateTime &time) const;
    
    /** Returns color name based on message type*/
    QString colorString(bool local, bool isSpooled) const; //TODO make it customizable
};

#endif

