#ifndef HAVE_CHAT_THEME
#define HAVE_CHAT_THEME

#include <Qt>
#include <QDateTime>

class ChatEvent;
class MessageChatEvent;
class FileTransferChatEvent;
class StatusChatEvent;
class EmoteChatEvent;
class SystemChatEvent;
class MoodChatEvent;
class TuneChatEvent;


/** Chat theme; Used by ChatEvents (create*Part) and ChatView */
class ChatTheme {

public:
    virtual QString createOutgoingMessagePart(const MessageChatEvent*) const = 0;
    virtual QString createIncomingMessagePart(const MessageChatEvent*) const = 0;

    /** Creates String using precomputed (precompiled) Contents/Resources/Incoming/FileTransfer.html template in HTMLChatTheme
        or handcoded (+ options) string creation in PlainChatTheme */
    virtual QString createFileTransferEventPart(const FileTransferChatEvent*) const = 0;
    virtual QString createStatusEventPart(const StatusChatEvent*) const = 0;
    virtual QString createEmoteEventPart(const EmoteChatEvent*) const = 0;
    virtual QString createSystemEventPart(const SystemChatEvent*) const = 0;
    virtual QString createMoodEventPart(const MoodChatEvent* event) const = 0;
    virtual QString createTuneEventPart(const TuneChatEvent* event) const = 0;


    virtual ~ChatTheme() {
    };

    /** Returns true if theme is valid (eg succesfully loaded) */
    virtual bool isValid() = 0;

    /** Contains Info related to ChatView session */
    struct ChatInfo {

        QDateTime timeOpened;
        
        QString chatName,
            sourceName,
            destinationName,
            destinationDisplayName,

            /** If empty default incoming icon/avatar will be used*/
            incomingIconPath,
            /** If empty default outgoing icon/avatar will be used*/
            outgoingIconPath;
    };
};

#endif
