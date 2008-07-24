#include "fileTransferChatEvent.h"


FileTransferChatEvent::FileTransferChatEvent() 
    :type(Initiated) {
    
}
QString FileTransferChatEvent::fileName() const {
    return _fileName;
}


void FileTransferChatEvent::setFileName(QString fileName) {
    _fileName = fileName;
}
