#ifndef _ADDURLDLG_H
#define	_ADDURLDLG_H

#include "ui_addurl.h"

/** Add URL/hyperlink dialog - prompts for URL and its description */
class AddUrlDlg : public QDialog, public Ui::AddUrl
{
        Q_OBJECT
public:
        AddUrlDlg(QWidget *parent=0);
        ~AddUrlDlg();
};

#endif

