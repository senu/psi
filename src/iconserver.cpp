#include "iconserver.h"
#include <QDebug>


void IconServer::registerIcon(const QString& name, QByteArray data) {
    dataMutex.lock();

    dict.insert(name, data);

    dataMutex.unlock();
}


QByteArray IconServer::getIcon(const QString& name) {
    dataMutex.lock();

    QByteArray data = dict[name];

    dataMutex.unlock();

    return data;
}


QByteArray IconServer::pixmapToPng(const QPixmap& pixmap) {
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG"); 

    qDebug() << "png data:" << buffer.data(); 
    return buffer.data();
}