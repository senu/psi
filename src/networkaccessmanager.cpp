#include "networkaccessmanager.h"

#include <QNetworkReply>
#include <QString>
#include <QDebug>

#include "iconreply.h"

NetworkAccessManager::NetworkAccessManager(QObject *parent)
    : QNetworkAccessManager(parent)
{
    QPixmap p(QSize(60,60));
    p.fill(QColor("red"));
    
    iconServer = new IconServer();
    iconServer->registerIcon("smile.png", IconServer::pixmapToPng(p)); 
    iconServer->registerIcon("icon_0114", IconServer::pixmapToPng(p)); 
}

QNetworkReply * NetworkAccessManager::createRequest ( Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0 ) {
	qDebug() << "create request" << op << req.url();
	
	QNetworkRequest req2(req);

	if(!req.url().toString().startsWith("icon://")) {	
//		req2.setUrl(QUrl("file:///home/senu/dev/psi/qt-x11-opensource-src-4.4.1-snapshot-20080423/doc-build/html-qt/images/qt-logo.png"));
		return QNetworkAccessManager::createRequest(op,req2,outgoingData);
	} 
	

	IconReply * repl = new IconReply(req.url(), iconServer);
	connect(repl, SIGNAL(finished()), SLOT(callFinished()));
	return repl;
} 

void NetworkAccessManager::callFinished() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	if (reply) {
		emit finished(reply);
	}
}


