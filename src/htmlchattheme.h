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

public:

    HTMLChatTheme();
    
    /** 
     * Constructor that reads theme from filesystem 
     *
     * \param path points to theme dir (Contents/ should be a sudir of path)
     */
    HTMLChatTheme(QString path);

    /** 
     * Returns theme path base href.
     * 
     * For example. ..../themeName/Contents/Resources/ 
     * 
     * There must be slash at the end! 
     */
    QString baseHref() const;
    
    /** Sets baseHref */
    void setBaseHref(QString);

    /** 
     * Returns list of theme variants.
     * 
     * Variants dont have '.css' suffix!
     */
    QStringList variants() const;

    /** 
     * Returns current theme variant.
     * 
     * It doesn't have '.css' suffix. 
     * Can be "" if no variant is selected.
     */
    QString currentVariant() const;

    /** Sets current theme variant (without .css suffix) */
    void setCurrentVariant(QString variant);

    /** 
     * Reads theme from filesystem 
     *
     * \param path points to theme dir (Contents/ should be a sudir of path)
     */
    void readTheme(QDir dir);

    /** Theme is valid if it was successfully loaded from filesystem */
    bool isValid();

    /** Returns headerTemplate */
    HTMLChatTemplate headerTemplate() const;

    /** Returns footerTemplate */
    HTMLChatTemplate footerTemplate() const;

    //reimplemented
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

    QString baseHref_;
    QStringList variants_;
    QString currentVariant_;
    bool isValid_;
    
    /** 
     * True if theme doesn't have Ougoing/ directory (Incoming/ is used instead) 
     * Well, it's true if Outoging/buddy_icon.png wasn't found.
     */
    bool noOutgoingDir; 
    

};

#endif
