#ifndef HAVE_RESOURCE_REPLY
#define HAVE_RESOURCE_REPLY

#include <Qt>
#include <QNetworkReply>
#include <QDebug>
#include <QTimer>
#include <QBuffer>

/** 
 * "Network" reply that returns icon (e.g .png file contents) n) from IconSever.
 * Used by QWebkit ( icon:// URLs )
 */
class IconReply : public QNetworkReply {
	Q_OBJECT

public:
	/** URL of icon, eg icon://smile.png */	
	IconReply(const QUrl& url);
	~IconReply();

	//reimplemented
	void abort();
	void close();
	qint64 readData(char *data, qint64 len);
	void setReadBufferSize ( qint64 size );
	qint64 bytesAvailable () const;
	bool open(OpenMode mode);
	qint64 size () const; 


private slots:
	/** We cannot emit finish() in constructor/before QNetworkAccessManager::createRequest() returns [Qt bug] */
	void dataReady();

private:
	/** Icon data */
	QBuffer iconBuffer;
};

#endif 
