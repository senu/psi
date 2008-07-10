#ifndef _JSNOTIFIER_H
#define	_JSNOTIFIER_H

#include <Qt>
#include <QtDebug>


/** Qt object inserted into Webkit to establish two-way communication between (js-c++) */
class JSNotifier : public QObject {

    Q_OBJECT

    public slots :

    /** psi_initDocument finished (called by js code) */
    void initFinished();

    /** Append event/message finished (called by js code) - now we can scroll view down, for example */
    void appendFinished();

signals:
    void onInitFinished();
    void onAppendFinished();


};


#endif

