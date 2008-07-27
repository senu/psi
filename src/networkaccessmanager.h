#ifndef _NETWORKACCESSMANAGER_H
#define _NETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include "iconserver.h"


/** Blocks internet connections and allows to use icon:// URLs in webkit-based ChatViews*/
class NetworkAccessManager : public QNetworkAccessManager {

    Q_OBJECT

public:
    /** 
     * Constructor. 
     * \param iconServer will be used to serve icon:// urls 
     */
    NetworkAccessManager(QObject *parent, IconServer* iconServer);

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
