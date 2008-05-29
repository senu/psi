#ifndef HAVE_CHAT_THEME
#define HAVE_CHAT_THEME

#include <Qt>


class ChatEvent;
class MessageChatEvent;
class FileTransferChatEvent;

class ChatTheme 													
{
  public:
	
	virtual QString createOutgoingMessagePart(const MessageChatEvent* ) = 0;

	/** creates part using precomputed (precompiled) Contents/Resources/Incoming/FileTransfer.html template in HTMLChatTheme
	 	or handcoded (+ options) string creation in PlainChatTheme */
	virtual QString createFileTransferEventPart(const FileTransferChatEvent* ) = 0; 
	virtual QString createIncomingMessagePart(const MessageChatEvent* ) = 0; 

	//reading theme, precomputing, misc	
};

#endif
