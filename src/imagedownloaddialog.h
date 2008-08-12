#ifndef _IMAGEDOWNLOADDIALOG_H
#define	_IMAGEDOWNLOADDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImage>
#include <QLabel>


class ImageDownloadDialog : public QDialog {

    Q_OBJECT
public:

    ImageDownloadDialog(QWidget* parent);
    ~ImageDownloadDialog();

    /** Returns downloadedImage */
    QImage downloadedImage() const;

    /** Returns urlEdit.text() */
    QString url() const;

    private 
slots:
    /** Closes dialog and aborts downloading file (if needed) */
    void cancel();

    /** Starts download urlEdit.text() */
    void startDownload();

    /** Reads image from imageReply and sets downloadedImage */
    void replyFinished(QNetworkReply* imageReply);

private:
    /** True if download was started */
    bool downloadStarted;
    
    /** Performs HTTP GET */
    QNetworkAccessManager *manager;

    /** Downloaded image or null QImage()*/
    QImage downloadedImage_;
    
    /** URL input */
    QLineEdit* urlEdit;

    /** QNetworkReply with an image */
    QNetworkReply* reply;
    
    QPushButton *okButton;
    QLabel *downloadingLabel;
};


#endif

