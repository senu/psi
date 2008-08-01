#include "addurldlg.h"
#include "iconset.h"
#include "psioptions.h"

AddUrlDlg::AddUrlDlg(QWidget *parent)
:QDialog(parent)
{
	if ( PsiOptions::instance()->getOption("options.ui.mac.use-brushed-metal-windows").toBool() )
		setAttribute(Qt::WA_MacMetalStyle);
	setupUi(this);
#ifndef Q_WS_MAC
	setWindowIcon(IconsetFactory::icon("psi/www").icon());
#endif
	setModal(true);

	connect(pb_close, SIGNAL(clicked()), SLOT(reject()));
	connect(pb_ok, SIGNAL(clicked()), SLOT(accept()));
}

AddUrlDlg::~AddUrlDlg()
{
}

