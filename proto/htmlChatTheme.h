#ifndef HAVE_HTML_CHAT_THEME
#define HAVE_HTML_CHAT_THEME

#include <Qt>

#include "chatTheme.h"
#include "htmlChatTemplate.h"
#include "fileTransferChatEvent.h"

class ChatTheme;
class FileTransferChatEvent;
class MessageChatEvent;
class ChatEvent;

class HTMLChatTheme : public ChatTheme 
{	
//...	
public:

	HTMLChatTheme();

	/** Reads templates from filesystem */
	void readTheme(QString themeName, QString variationName);
	
	QString createIncomingMessagePart(const MessageChatEvent *);
	
	QString createOutgoingMessagePart(const MessageChatEvent *);
	
	QString createFileTransferEventPart(const FileTransferChatEvent * event);

private:
	HTMLChatTemplate incomingConsecutiveMessageTemplate;
	HTMLChatTemplate incomingNextMessageTemplate;

	HTMLChatTemplate outgoingConsecutiveMessageTemplate;
	HTMLChatTemplate outgoingNextMessageTemplate;

	HTMLChatTemplate fileTransferMessageTemplate;

};

#endif
