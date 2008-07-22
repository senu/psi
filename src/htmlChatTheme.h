#ifndef HAVE_HTML_CHAT_THEME
#define HAVE_HTML_CHAT_THEME

#include <Qt>
#include <QDir>

#include "chatTheme.h"
#include "htmlChatTemplate.h"
#include "htmlchatemotetemplate.h"

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


/** ChatTheme used by HTMLChatView */
class HTMLChatTheme : public ChatTheme {

    //...	
public:

    HTMLChatTheme();
    /** Reads theme from filesystem */
    HTMLChatTheme(QString path);

    /** Returns theme path sth/Contents/Resources/ ; there must be slash at the end! */
    QString baseHref() const;
    void setBaseHref(QString);

    /** Returns list of theme variants (without .css suffix!)*/
    QStringList variants() const;

    /** Returns current theme variant (withou .css suffix). Can be "" */
    QString currentVariant() const;

    /** Sets current theme variant (withou .css suffix) */
    void setCurrentVariant(QString variant);

    /** Reads theme from filesystem (path to Contents/Resources) */
    void readTheme(QDir dir);

    bool isValid();

    QString createIncomingMessagePart(const MessageChatEvent *) const;
    QString createOutgoingMessagePart(const MessageChatEvent *) const;

    QString createFileTransferEventPart(const FileTransferChatEvent * event) const;
    QString createStatusEventPart(const StatusChatEvent * event) const;

    QString createEmoteEventPart(const EmoteChatEvent * event) const;
    QString createMoodEventPart(const MoodChatEvent* event) const;
    QString createTuneEventPart(const TuneChatEvent* event) const;
    QString createSystemEventPart(const SystemChatEvent*) const;

    /** Fills part (footer/header) with keywords (chatName, timeOpened) */
    void fillPartWithThemeKeywords(HTMLChatPart& part, ChatTheme::ChatInfo sessionInfo) const;

    HTMLChatTemplate headerTemplate; //TODO accessors
    HTMLChatTemplate footerTemplate;

    /** True if paths and varians are equal */
    bool operator==(const HTMLChatTheme& other) const;
    bool operator!=(const HTMLChatTheme& other) const;


private:

    /** Fills part with user (eg nick) keywords from event (common for in/out next/cons messages and emote) */
    void fillPartWithUserKeywords(HTMLChatPart& part, const UserChatData* event) const;

    /** 
     * Fills part with keywords from event; %message% = eventText (common for eg filetransfer, mood) 
	 *  
	 * Not for messages nor emote!
	 */
    void fillPartWithEventKeywords(HTMLChatPart& part, const ChatEvent* event, QString eventText) const;

    /** Replaces %time%, %shortTime%, etc */
    void fillPartWithTimeKeywords(HTMLChatPart& part, const AbstractChatEvent* event) const;
	
    /** Returns dir/relativePath (to Contents dir) */
    QString readFileContents(QDir dir, QString relativePath);


    HTMLChatTemplate incomingConsecutiveMessageTemplate;
    HTMLChatTemplate incomingNextMessageTemplate;

    HTMLChatTemplate outgoingConsecutiveMessageTemplate;
    HTMLChatTemplate outgoingNextMessageTemplate;

    HTMLChatTemplate fileTransferEventTemplate;
    HTMLChatTemplate systemEventTemplate;
    HTMLChatTemplate moodEventTemplate;
    HTMLChatTemplate tuneEventTemplate;

    HTMLChatEmoteTemplate incomingEmoteEventTemplate;
    HTMLChatEmoteTemplate outgoingEmoteEventTemplate;

    QString _baseHref;
    QStringList _variants;
    QString _currentVariant;
    bool _isValid;

};

#endif
