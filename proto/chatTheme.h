#ifndef HAVE_CHAT_THEME
#define HAVE_CHAT_THEME

#include <Qt>


class ChatEvent;
class MessageChatEvent;
class FileTransferChatEvent;
class StatusChatEvent;

/** Chat theme; Used by ChatEvents (create*Part) and ChatView */
class ChatTheme 													
{
  public:
	virtual QString createOutgoingMessagePart(const MessageChatEvent* ) const = 0;
	virtual QString createIncomingMessagePart(const MessageChatEvent* ) const = 0; 

	/** creates part using precomputed (precompiled) Contents/Resources/Incoming/FileTransfer.html template in HTMLChatTheme
	 	or handcoded (+ options) string creation in PlainChatTheme */
	virtual QString createFileTransferEventPart(const FileTransferChatEvent* ) const = 0; 
	virtual QString createStatusEventPart(const StatusChatEvent* ) const = 0; 

	virtual ~ChatTheme() {};
};

#endif
