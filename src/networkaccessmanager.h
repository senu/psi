#ifndef _NETWORKACCESSMANAGER_H
#define _NETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include "iconserver.h"


/** Blocks internet connections and allows to use icon:// URLs in webkit-based ChatViews*/
class NetworkAccessManager : public QNetworkAccessManager {

    Q_OBJECT

public:
    NetworkAccessManager(QObject *parent = 0);

    private
slots:
    /** Called by QNetworkReply::finish(); reemits finish(reply) */
    void callFinished();

protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData);

    /** For icon::// serving */
    IconServer* iconServer;
};

#endif
