#ifndef HAVE_HTML_CHAT_THEME
#define HAVE_HTML_CHAT_THEME

#include <Qt>

#include "chatTheme.h"
#include "fileTransferChatEvent.h"

class ChatTheme;
class FileTransferChatEvent;
class MessageChatEvent;
class ChatEvent;

class HTMLChatTheme : public ChatTheme 
{	
//...	
public:
	//precomputed templates/html parts reading. 
	void readTheme(QString themeName, QString variationName);
	
	QString createIncomingMessagePart(const MessageChatEvent *);
	
	QString createOutgoingMessagePart(const MessageChatEvent *);
	
	QString createFileTransferEventPart(const FileTransferChatEvent * event);

};

#endif
