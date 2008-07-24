#include "iconreply.h"
#include <QFile>

IconReply::IconReply(const QUrl& url) : QNetworkReply() 
{
	setOpenMode(QIODevice::ReadOnly | QIODevice::Unbuffered);	
	setUrl(url);

	QFile f("/home/senu/2008-06-30-120934_1280x1024_scrot.png");

	f.open(QIODevice::ReadOnly);
	iconBuffer.setData(f.readAll());
	iconBuffer.open(QIODevice::ReadOnly);

	qDebug() << "IR::IconReply()" << url << iconBuffer.bytesAvailable();
	QTimer::singleShot(0, this, SLOT(dataReady()));
}

void IconReply::abort() {
	qDebug() << "IR::abort()";				
}

void IconReply::close() {
	qDebug() << "IR::close()";				
}

qint64 IconReply::bytesAvailable () const {
	qDebug() << "IR::bytesAvailable()" << iconBuffer.bytesAvailable();				
	return iconBuffer.bytesAvailable();
		
}

qint64 IconReply::readData(char *data, qint64 len) {
	qDebug() << "IR::readData()" << len << iconBuffer.bytesAvailable();
	return iconBuffer.read(data,len);
}

void IconReply::setReadBufferSize ( qint64 size ) {
	Q_UNUSED(size);
	qDebug() << "IR::setReadBufferSize()";
	Q_ASSERT(0); //should never happened
}

IconReply::~IconReply() {
	qDebug() << "IR::~IconReply()";
}

void IconReply::dataReady() {
	qDebug() << "IR::dataReady()";

	emit downloadProgress(0,580);
	emit downloadProgress(580,580);
	emit readyRead();
	emit finished();
}

bool IconReply::open(OpenMode mode) {
	Q_UNUSED(mode);
	qDebug() << "IR::open()";
	Q_ASSERT(0); //should never happened
}

qint64 IconReply::size () const {
	qDebug() << "IR::size()";
	return bytesAvailable(); //well, should never happended too
}
