#ifndef HAVE_HTML_CHAT_THEME
#define HAVE_HTML_CHAT_THEME

#include <Qt>
#include <QDir>

#include "chattheme.h"
#include "htmlchattemplate.h"
#include "htmlchatemotetemplate.h"

#include "filetransferchatevent.h"
#include "statuschatevent.h"
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

    /** Returns headerTemplate */
    HTMLChatTemplate headerTemplate() const;

    /** Returns footerTemplate */
    HTMLChatTemplate footerTemplate() const;

    QString createIncomingMessagePart(const MessageChatEvent *) const;
    QString createOutgoingMessagePart(const MessageChatEvent *) const;
    QString createEmoteEventPart(const EmoteChatEvent * event) const;
   
    /** Overloaded version */
    HTMLChatPart createIncomingMessageHTMLPart(const MessageChatEvent *) const;
    
    /** Overloaded version */
    HTMLChatPart createOutgoingMessageHTMLPart(const MessageChatEvent *) const;
    
    /** Overloaded version */
    HTMLChatPart createEmoteEventHTMLPart(const EmoteChatEvent * event) const;

    QString createFileTransferEventPart(const FileTransferChatEvent * event) const;
    QString createStatusEventPart(const StatusChatEvent * event) const;

    QString createMoodEventPart(const MoodChatEvent* event) const;
    QString createTuneEventPart(const TuneChatEvent* event) const;
    QString createSystemEventPart(const SystemChatEvent*) const;

    /** Fills part (footer/header) with keywords (chatName, timeOpened) */
    void fillPartWithThemeKeywords(HTMLChatPart& part, ChatTheme::ChatInfo sessionInfo) const;

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

    //TODO!!!
    
    /** Default %userIconPath% for incoming messages*/
    QString defaultIncomingAvatar() const;
    
    /** 
     * Default %userIconPath% for outgoing messages. 
     * 
     * We need that because there can be no Outoging/ dir
     */
    QString defaultOutgoingAvatar() const;


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

    HTMLChatTemplate headerTemplate_;
    HTMLChatTemplate footerTemplate_;

    QString _baseHref;
    QStringList _variants;
    QString _currentVariant;
    bool _isValid;
    
    /** 
     * True if theme doesn't have Ougoing/ directory (Incoming/ is used) 
     * Well, it's true if Outoging/buddy_icon.png doesnt is not found.
     */
    bool noOutgoingDir; 
    

};

#endif
