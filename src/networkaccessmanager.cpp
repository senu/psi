#include "networkaccessmanager.h"

#include <QNetworkReply>
#include <QString>
#include <QDebug>

#include "iconreply.h"
#include "iconset.h"


NetworkAccessManager::NetworkAccessManager(QObject *parent, IconServer* iconServer_)
: QNetworkAccessManager(parent), iconServer(iconServer_) {


    foreach(QString iconName, IconsetFactory::icons()) { //TODO
        if (!iconName.isEmpty()) {
            iconServer->registerIcon(iconName, IconServer::pixmapToPng(IconsetFactory::iconPixmap(iconName)));
        }
    }
    //iconServer->registerIcon("icon_0114", IconServer::pixmapToPng(p)); 
}


QNetworkReply * NetworkAccessManager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0) {
    qDebug() << "create request" << op << req.url();

    //download icon
    if (req.url().toString().startsWith("icon://")) {
        IconReply * repl = new IconReply(req.url(), iconServer);
        connect(repl, SIGNAL(finished()), SLOT(callFinished()));
        return repl;
    }

    //download local file
    if (req.url().toString().startsWith("file://")) {
        return QNetworkAccessManager::createRequest(op, req, outgoingData);
    }

    //deny all other access
    QNetworkRequest req2(req);
    req2.setUrl(QUrl());

    QNetworkReply * reply = QNetworkAccessManager::createRequest(op, req2, outgoingData);
    connect(reply, SIGNAL(finished()), SLOT(callFinished()));
//    reply->setError(QNetworkReply::ContentAccessDenied, "Access denied"); //TODO
    
    return reply; //TODO ctso
}


void NetworkAccessManager::callFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        emit finished(reply);
    }
}


