#ifndef HAVE_FILE_TRANSFER_CHAT_EVENT
#define HAVE_FILE_TRANSFER_CHAT_EVENT

#include <Qt>
#include <QString>

#include "chatEvent.h"
#include "chatTheme.h"

class ChatTheme;
class AstractChatEvent;

/** FileTransfer (init/abort/finished) ChatEvent */
class FileTransferChatEvent : public ChatEvent 
{
  public:	
	enum FileTransferEventType {
		Initiated,
		Aborted,
		Finished,
	};

	FileTransferEventType type;

	QString fileName() const;
	void setFileName(QString);
	

	QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
		return theme.createFileTransferEventPart(this);
	}

private:	
	QString _fileName; //need accessors
};

#endif
