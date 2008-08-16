#ifndef HAVE_FILE_TRANSFER_CHAT_EVENT
#define HAVE_FILE_TRANSFER_CHAT_EVENT

#include <Qt>
#include <QString>

#include "chatevent.h"
#include "chattheme.h"

class ChatTheme;
class AstractChatEvent;


/** FileTransfer (init/abort/finished) ChatEvent */
class FileTransferChatEvent : public ChatEvent {

public:

    //TODO 22 finished! not implemented in psi
    enum FileTransferEventType {

        Initiated,
        Aborted,
        Finished,
    };

    FileTransferChatEvent();

    /** Type of FileTransferEvent */
    FileTransferEventType type;

    /** Returns fileName */
    QString fileName() const;

    /** Sets fileName */
    void setFileName(QString fileName);


    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
        return theme.createFileTransferEventPart(this);
    }

private:
    QString _fileName; //need accessors
};

#endif
