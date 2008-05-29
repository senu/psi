#ifndef HAVE_FILE_TRANSFER_CHAT_EVENT
#define HAVE_FILE_TRANSFER_CHAT_EVENT

#include <Qt>
#include <QString>

#include "chatEvent.h"
#include "chatTheme.h"

class ChatTheme;
class ChatEvent;

class FileTransferChatEvent : public ChatEvent 
{
public:	
	enum FileTransferEventType {
		Initiated,
		Aborted,
		Finished,
	};

	FileTransferEventType type;
	QString fileName; //need accessors

	virtual QString getRightTemplateAndFillItWithData(ChatTheme& theme) {

		return theme.createFileTransferEventPart(this);
	}
};

#endif
