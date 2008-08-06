#ifndef _FINDDIALOG_H
#define	_FINDDIALOG_H

#include <QDialog>
#include <QLineEdit>

/** Dialog for text searching */
class FindDialog : public QDialog {

    Q_OBJECT
public:
    FindDialog(const QString &, QWidget *parent = 0, const char *name = 0);
    ~FindDialog();

    void found();
    void error(const QString &);

signals:
    void find(const QString &);

    private
slots:
    void doFind();

private:
    QLineEdit *le_input;
};


#endif

