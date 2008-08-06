#include "finddialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QMessageBox>

FindDialog::FindDialog(const QString &str, QWidget *parent, const char *name)
: QDialog(parent, name, false) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("Find"));
    QVBoxLayout *vb = new QVBoxLayout(this, 4);
    QHBoxLayout *hb = new QHBoxLayout(vb);
    QLabel *l = new QLabel(tr("Find:"), this);
    hb->addWidget(l);
    le_input = new QLineEdit(this);
    hb->addWidget(le_input);
    vb->addStretch(1);

    QFrame *Line1 = new QFrame(this);
    Line1->setFrameShape(QFrame::HLine);
    Line1->setFrameShadow(QFrame::Sunken);
    Line1->setFrameShape(QFrame::HLine);
    vb->addWidget(Line1);

    hb = new QHBoxLayout(vb);
    hb->addStretch(1);
    QPushButton *pb_close = new QPushButton(tr("&Close"), this);
    connect(pb_close, SIGNAL(clicked()), SLOT(close()));
    hb->addWidget(pb_close);
    QPushButton *pb_find = new QPushButton(tr("&Find"), this);
    pb_find->setDefault(true);
    connect(pb_find, SIGNAL(clicked()), SLOT(doFind()));
    hb->addWidget(pb_find);
    pb_find->setAutoDefault(true);

    resize(200, minimumSizeHint().height());

    le_input->setText(str);
    le_input->setFocus();
}


FindDialog::~FindDialog() {
}


void FindDialog::found() {
    // nothing here to do...
}


void FindDialog::error(const QString &str) {
    QMessageBox::warning(this, tr("Find"), tr("Search string '%1' not found.").arg(str));
    le_input->setFocus();
}


void FindDialog::doFind() {
    emit find(le_input->text());
}
