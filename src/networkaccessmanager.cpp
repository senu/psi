#include "networkaccessmanager.h"

#include <QNetworkReply>
#include <QString>
#include <QDebug>

#include "iconreply.h"

NetworkAccessManager::NetworkAccessManager(QObject *parent)
    : QNetworkAccessManager(parent)
{
}

QNetworkReply * NetworkAccessManager::createRequest ( Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0 ) {
	qDebug() << "create request" << op << req.url();
	
	QNetworkRequest req2(req);

	if(!req.url().toString().endsWith(".png")) {	
//		req2.setUrl(QUrl("file:///home/senu/dev/psi/qt-x11-opensource-src-4.4.1-snapshot-20080423/doc-build/html-qt/images/qt-logo.png"));
		return QNetworkAccessManager::createRequest(op,req2,outgoingData);
	} 
	

	IconReply * repl = new IconReply(req.url());
	connect(repl, SIGNAL(finished()), SLOT(callFinished()));
	return repl;
} 

void NetworkAccessManager::callFinished() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	if (reply) {
		emit finished(reply);
	}
}


