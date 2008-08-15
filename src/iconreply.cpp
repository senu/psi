#include "iconreply.h"

#include <QFile>


IconReply::IconReply(const QUrl& url, const IconServer* iconSever) : QNetworkReply() {
    setOpenMode(QIODevice::ReadOnly | QIODevice::Unbuffered);
    setUrl(url);

    iconBuffer.setData(iconSever->getIcon(url.toString().mid(7))); //icon://
    iconBuffer.open(QIODevice::ReadOnly);

    qDebug() << "IR::IconReply()" << url << iconBuffer.bytesAvailable();
    QTimer::singleShot(0, this, SLOT(dataReady()));
}

IconReply::IconReply() {
    setOpenMode(QIODevice::ReadOnly | QIODevice::Unbuffered);
    setUrl(QUrl());

    iconBuffer.open(QIODevice::ReadOnly);

    qDebug() << "access denied IR::IconReply()" << iconBuffer.bytesAvailable();
    QTimer::singleShot(0, this, SLOT(dataReady()));
    
}

void IconReply::abort() {
    qDebug() << "IR::abort()";
}


void IconReply::close() {
    qDebug() << "IR::close()";
}


qint64 IconReply::bytesAvailable() const {
    qDebug() << "IR::bytesAvailable()" << iconBuffer.bytesAvailable();
    return iconBuffer.bytesAvailable();

}


qint64 IconReply::readData(char *data, qint64 len) {
    qDebug() << "IR::readData()" << len << iconBuffer.bytesAvailable();
    return iconBuffer.read(data, len);
}


void IconReply::setReadBufferSize(qint64 size) {
    Q_UNUSED(size);
    qDebug() << "IR::setReadBufferSize()";
    Q_ASSERT(0); //should never happened
}


IconReply::~IconReply() {
    qDebug() << "IR::~IconReply()";
}


void IconReply::dataReady() {
    qDebug() << "IR::dataReady()";

    qint64 totalSize = iconBuffer.bytesAvailable();
    
    if (!totalSize) { //not in IconServer or (internet) access denied
        setError(QNetworkReply::ContentAccessDenied, "Access Denied");
        emit error(QNetworkReply::ContentAccessDenied);
        emit finished();
        return; 
    }
    
    emit downloadProgress(0, totalSize);
    emit downloadProgress(totalSize, totalSize);
    emit readyRead();
    emit finished();
}


bool IconReply::open(OpenMode mode) {
    Q_UNUSED(mode);
    qDebug() << "IR::open()";
    Q_ASSERT(0); //should never happened
}


qint64 IconReply::size() const {
    qDebug() << "IR::size()";
    return bytesAvailable(); //well, should never happended too
}
