#include "iconserver.h"
#include <QDebug>

class IconServer;


void IconServer::registerIcon(const QString& name, QByteArray data) {
    dataMutex.lock();

    qDebug() << "registerIcon()" << name << data.size();
    dict.insert(name, data);

    dataMutex.unlock();
}


QByteArray IconServer::getIcon(const QString& name) const {
    dataMutex.lock();

    qDebug() << "getIcon()" << name;
    QByteArray data = dict[name];

    dataMutex.unlock();

    return data;
}


QByteArray IconServer::pixmapToPng(const QPixmap& pixmap) {
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");

    return buffer.data();
}


void IconServer::unregisterAll(const QStringList& names) {
    dataMutex.lock();
    qDebug() << "unregisterAll()" << names;


    foreach(QString name, names) {
        dict.remove(name);
    }

    dataMutex.unlock();
}


void IconServer::registerAll(QStringList names, const QList<const QPixmap*>& icons) { //TODO qt moc cannot handle const list<pair>& 
    dataMutex.lock();
    qDebug() << "registerAll()" << names;

    QPair<QString, const QPixmap*> pair;
    /* TODO
    foreach(pair, icons) {
        dict.insert(pair.first, IconServer::pixmapToPng(*pair.second));
    }
     */

    dataMutex.unlock();
}
