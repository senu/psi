#ifndef _EVENTVIEW_H
#define	_EVENTVIEW_H

#include <QWebView>
#include "networkaccessmanager.h"


/**
 * Webkit-based event viewer (used in EventDlg).
 * 
 * It offers better XHTML(-IM) rendering.
 * It's a QWebPage with disabled JavaScript/Network access/Plugins/Objects
 * It also has icon:// URL support
 */
class EventView : public QWebView {
    Q_OBJECT

public:
    /** IconServer will be used to display icons:// */
    EventView(QWidget* parent, IconServer* iconServer);

    /** 
     * Displays xhtmlText.
     *
     * \param xhtmlText is XHTML string. It can have icon:// URLs
     */
    void displayText(const QString& xhtmlText);

    /**
     * Returns XHTML source of displayed event.
     *
     * Used in quote-reply.
     * Returns underlaying document (<html>...</html>)
     */
    QString getHtml();

    /** Scrolls to top of the view */
    void scrollToTop();

signals:

    /** Emitted when user click on URL */
    void openURL(QString);

private slots:
    
    /** Emits openURL() */
    void onLinkClicked(const QUrl& url);

protected:

    /** Creates menu with Copy action */
    void contextMenuEvent(QContextMenuEvent* event);
    
    NetworkAccessManager *networkManager;

};

#endif

