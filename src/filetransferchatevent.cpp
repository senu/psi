#include "filetransferchatevent.h"


FileTransferChatEvent::FileTransferChatEvent() : type(Initiated) {

}


QString FileTransferChatEvent::fileName() const {
    return fileName_;
}


void FileTransferChatEvent::setFileName(QString fileName) {
    fileName_ = fileName;
}


QString FileTransferChatEvent::getRightTemplateAndFillItWithData(const ChatTheme& theme) const {
    return theme.createFileTransferEventPart(this);
}
