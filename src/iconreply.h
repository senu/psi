#ifndef HAVE_RESOURCE_REPLY
#define HAVE_RESOURCE_REPLY

#include <QNetworkReply>
#include <QDebug>
#include <QTimer>
#include <QBuffer>

#include "iconserver.h"


/** 
 * "Network" reply that "downloads" icon from IconServer. 
 * 
 * It's (another) bridge between C++ part of Psi and Webkit-based ChatView.
 * 
 * NOTE: Although it's *Icon*Reply and there's *Icon*Server you can download any data from
 * NOTE: IconServer using icon:// URL. Name ResouceReply would be a little confusing, I think.
 *
 * BTW, QWebkit doesn't cache data:// URI
 *
 * NOTE: Webkit IconReplies are cached. You may set QNetworkRequest::LastModifiedHeader HTTP header, 
 * NOTE: or QNetworkRequest::AlwaysNetwork to force download from the iconServer.
 * 
 * Used by QWebkit ( icon:// URLs )
 */
class IconReply : public QNetworkReply {

    Q_OBJECT

public:
    /** URL of icon, eg icon://smile.png; icon will be "downloaded" from \param iconServer */
    IconReply(const QUrl& url, const IconServer* iconServer);

    /** Construct IconReply that fails with ContentAccessDenied error */
    IconReply();
    ~IconReply();

    //reimplemented
    void abort();
    void close();
    qint64 readData(char *data, qint64 len);
    void setReadBufferSize(qint64 size);
    qint64 bytesAvailable() const;
    bool open(OpenMode mode);
    qint64 size() const;


    private
slots:

    /**
     * Emits finished().
     * 
     * We cannot emit finished() in constructor.
     *
     * To be precise QNetworkAccessManager::createRequest() must return before we emit finished()
     * It's Qt bug.
     */
    void dataReady();

private:
    /** Icon data */
    QBuffer iconBuffer;
};

#endif 
