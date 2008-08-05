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
     * Used in quote-reply 
     */
    QString getHtml(); //TODO 21 return only <body/>
    
protected:    
    NetworkAccessManager *networkManager;

};

#endif

