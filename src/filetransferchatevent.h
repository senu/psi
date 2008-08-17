#ifndef HAVE_FILE_TRANSFER_CHAT_EVENT
#define HAVE_FILE_TRANSFER_CHAT_EVENT

#include <QString>

#include "chatevent.h"
#include "chattheme.h"

/**
 * FileTransfer ChatEvent
 * 
 * Displayed when user receives/aborts File Transfer.  
 */
class FileTransferChatEvent : public ChatEvent {

public:

    //TODO 22 finished! not implemented in psi
    enum FileTransferEventType {

        Initiated,
        Aborted,
        Finished,
    };

    /**
     * Constructor.
     *
     * type = Initiated.
     */
    FileTransferChatEvent();

    /** Type of FileTransferEvent */
    FileTransferEventType type;

    /** Returns fileName */
    QString fileName() const;

    /** Sets fileName */
    void setFileName(QString fileName);

    //reimplemented
    QString getRightTemplateAndFillItWithData(const ChatTheme& theme) const;

private:
    QString fileName_; 
};

#endif
