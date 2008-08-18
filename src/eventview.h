#ifndef _EVENTVIEW_H
#define	_EVENTVIEW_H

#include "webview.h"
#include "jsnotifier.h"


/**
 * Webkit-based event viewer (used in EventDlg).
 * 
 * It offers better XHTML(-IM) rendering and has icon:// URL support
 */
class EventView : public WebView {

    Q_OBJECT

public:
    /** IconServer will be used to display icon:// URLs */
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

signals:

    /** Emitted when user click on URL */
    void openURL(QString);

    private 
slots:

    /** Emits openURL() */
    void onLinkClicked(const QUrl& url);

    /** Loads JavaScript Psi code from file and connects jsNotifier signals (image unbanning) */
    void loadAndBindJS(bool ok);
    
    /** 
     * Validates and displays event.
     */
    void onInitDocumentFinished();

private:
    
    /** JavaScript - C++ bridge */
    JSNotifier jsNotifier;

    /** Holds displayed text */
    QString eventBody;
};

#endif

