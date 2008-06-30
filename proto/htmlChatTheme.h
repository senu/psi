#ifndef HAVE_HTML_CHAT_THEME
#define HAVE_HTML_CHAT_THEME

#include <Qt>
#include <QDir>

#include "chatTheme.h"
#include "htmlChatTemplate.h"
#include "fileTransferChatEvent.h"
#include "statusChatEvent.h"
#include "chatMessageEvent.h"

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

    /** Reads templates from filesystem */
    //void readTheme(QString themeName, QString variationName);
	
	/** Returns theme path (-/Contents) */
	QString baseHref() const;
	void setBaseHref(QString);

	/** Returns list of theme variants (without .css suffix!)*/
	QStringList variants() const;

	/** Returns current theme variant (withou .css suffix). Can be "" */
	QString currentVariant() const;
	
	/** Sets current theme variant (withou .css suffix) */
	void setCurrentVariant(QString variant);

    QString createIncomingMessagePart(const MessageChatEvent *) const;
    QString createOutgoingMessagePart(const MessageChatEvent *) const;

    QString createFileTransferEventPart(const FileTransferChatEvent * event) const;
    QString createStatusEventPart(const StatusChatEvent * event) const;

    /** Fills part (footer/header) with keywords (chatName, timeOpened) */
	void fillPartWithThemeKeywords(HTMLChatPart& part, QString chatName, QDateTime timeOpened) const;
	
	HTMLChatTemplate headerTemplate; //TODO accessors
    HTMLChatTemplate footerTemplate;

private:

    /** Fills part with keywords from event (common for in/out next/cons messages) */
    void fillPartWithMessageKeywords(HTMLChatPart& part, const MessageChatEvent* event) const;

    /** returns dir/relativePath (to Contents dir) */
    QString readFileContents(QDir dir, QString relativePath);

    HTMLChatTemplate incomingConsecutiveMessageTemplate;
    HTMLChatTemplate incomingNextMessageTemplate;

    HTMLChatTemplate outgoingConsecutiveMessageTemplate;
    HTMLChatTemplate outgoingNextMessageTemplate;

    HTMLChatTemplate fileTransferEventTemplate;

	QString _baseHref;
	QStringList _variants;
	QString _currentVariant;

};

#endif
