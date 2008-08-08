#include "networkaccessmanager.h"

#include <QNetworkReply>
#include <QString>
#include <QDebug>

#include "iconreply.h"
#include "iconset.h"


NetworkAccessManager::NetworkAccessManager(QObject *parent, IconServer* iconServer_)
: QNetworkAccessManager(parent), iconServer(iconServer_) {
    
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

    QNetworkReply * reply = new IconReply(); //finishes with error
    connect(reply, SIGNAL(finished()), SLOT(callFinished()));
    
    return reply;
}


void NetworkAccessManager::callFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        emit finished(reply);
    }
}

