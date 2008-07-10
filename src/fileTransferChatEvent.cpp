#include "fileTransferChatEvent.h"


QString FileTransferChatEvent::fileName() const {
    return _fileName;
}


void FileTransferChatEvent::setFileName(QString fileName) {
    _fileName = fileName;
}
