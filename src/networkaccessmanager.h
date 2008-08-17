#ifndef _NETWORKACCESSMANAGER_H
#define _NETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QStringList>
#include <QMutex>

#include "iconserver.h"


/** Blocks internet connections and allows to use icon:// URLs in webkit-based ChatViews*/
class NetworkAccessManager : public QNetworkAccessManager {

    Q_OBJECT

public:
    /** 
     * Constructor. 
     *
     * \param iconServer will be used to serve icon:// urls 
     */
    NetworkAccessManager(QObject *parent, IconServer* iconServer);
    ~NetworkAccessManager();

    /** Add URL to whiteList. */
    void addUrlToWhiteList(const QString& url);

    private
slots:
        
    /** 
     * Called by QNetworkReply::finish(). 
     * 
     * Emitts finish(reply) 
     */
    void callFinished();

protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData);

    /** For icon::// serving */
    IconServer* iconServer;

    /* 
     * List of whitelisted URLs.
     *
     * Access to whitelisted URLs is not denied.
     */
    QStringList whiteList;

    /** 
     * Mutal exclusion for whitList. 
     * 
     * WhiteList can be accessed by Webkit (createRequest()) 
     * and Psi (addUrlToWhiteList()) simultaneously)
     */
    QMutex whiteListMutex;
};

#endif
