#include <QDebug>

#include "iconserver.h"

class IconServer;


void IconServer::registerIcon(const QString& name, QByteArray data) {
    dataMutex.lock();

    dict.insert(name, data);

    dataMutex.unlock();
}


QByteArray IconServer::getIcon(const QString& name) const {
    dataMutex.lock();

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

    foreach(QString name, names) {
        dict.remove(name);
    }

    dataMutex.unlock();
}


void IconServer::registerAll(QStringList names, const QList<const QPixmap*>& icons) { //qt moc cannot handle const list<pair>& 
    dataMutex.lock();

    Q_ASSERT(icons.size() == names.size());

    for (int i = 0; i < names.size(); i++) {
        dict.insert(names.at(i), IconServer::pixmapToPng(*icons.at(i)));
    }

    dataMutex.unlock();
}
