#ifndef _JSNOTIFIER_H
#define	_JSNOTIFIER_H

#include <Qt>
#include <QtDebug>


/** 
 * Qt object inserted into Webkit to establish two-way communication between Webkit JS and C++.
 *
 * Maybe JSBridge would be a better name.
 */
class JSNotifier : public QObject {

    Q_OBJECT

    public slots :

    /** 
     * psi_initDocument finished (it's JavaScript code) 
     *
     * //NOTE: if you connect to this signal, read a NOTEs: in HTMLCHatView::onEmptyDocumentLoaded
     */
    void initFinished();

    /** Append event/message finished (called by js code) - now we can scroll view down, for example */
    void appendFinished();

    /** 
     * Emits onAddToWhiteListRequest. 
     *
     * JavaScript call this when someone/something (most likely user) wants to see blcoked image.
     */
    void addToWhiteListRequested(const QString& url);

signals:
    void onInitFinished();
    void onAppendFinished();
    void onAddToWhiteListRequested(const QString& url);


};


#endif

