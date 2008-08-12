#include "imagedownloaddialog.h"
#include "lineedit.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>


ImageDownloadDialog::ImageDownloadDialog(QWidget* parent) : QDialog(parent), reply(0), downloadStarted(0) {
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    setWindowTitle(tr("Insert image"));
    QVBoxLayout *vb = new QVBoxLayout(this, 4);
    QHBoxLayout *hb = new QHBoxLayout(vb);
    QLabel *l = new QLabel(tr("URL:"), this);
    hb->addWidget(l);
    urlEdit = new QLineEdit(this);
    hb->addWidget(urlEdit);
    vb->addStretch(1);

    QFrame *Line1 = new QFrame(this);
    Line1->setFrameShape(QFrame::HLine);
    Line1->setFrameShadow(QFrame::Sunken);
    Line1->setFrameShape(QFrame::HLine);
    vb->addWidget(Line1);

    hb = new QHBoxLayout(vb);
    hb->addStretch(1);

    downloadingLabel = new QLabel(tr("Downloading..."), this);
    hb->addWidget(downloadingLabel);
    downloadingLabel->setVisible(false);

    QPushButton *cancelButton = new QPushButton(tr("&Cancel"), this);
    connect(cancelButton, SIGNAL(clicked()), SLOT(cancel()));
    hb->addWidget(cancelButton);
    cancelButton->setAutoDefault(true);
    cancelButton->setDefault(true);

    okButton = new QPushButton(tr("&OK"), this);
    connect(okButton, SIGNAL(clicked()), SLOT(startDownload()));
    hb->addWidget(okButton);
    

    resize(350, minimumSizeHint().height());

    connect(urlEdit, SIGNAL(returnPressed()), SLOT(startDownload()));
    urlEdit->setFocus();
}


ImageDownloadDialog::~ImageDownloadDialog() {

}


void ImageDownloadDialog::cancel() {
    if (downloadStarted) {
        reply->abort();
    }

    reject();
}


void ImageDownloadDialog::startDownload() {
    if (!downloadStarted) {
        reply = manager->get(QNetworkRequest(url()));
        downloadStarted = true;

        urlEdit->setReadOnly(true);
        okButton->setEnabled(false);
        downloadingLabel->setVisible(true);
    }
}


QImage ImageDownloadDialog::downloadedImage() const {
    return downloadedImage_;
}


void ImageDownloadDialog::replyFinished(QNetworkReply* imageReply) {

    if (imageReply->error() == QNetworkReply::NoError) {
        downloadedImage_.load(imageReply, 0);
    }

    accept();
}


QString ImageDownloadDialog::url() const {
    return urlEdit->text();
}