#ifndef _WEBVIEW_H
#define	_WEBVIEW_H

#include <QWebView>
#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>

#include "networkaccessmanager.h"


/**
 * Extended QWebView.
 *
 * It's used in EventView and HTMLChatView.
 * Provides evaluateJavaScript escaping and secure NetworkManager with icon:// URL 
 * support and \<img\> whitelisting. 
 *
 * Better name for it would be: PsiWebView, but it's used in HTMLChatView which is 
 * Psi-unaware.  
 */
class WebView : public QWebView {

    Q_OBJECT
public:

    /** IconServer will be used to display icon:// */
    WebView(QWidget* parent, IconServer* iconServer);

    /**
     * Scrolls the vertical scroll bar to its maximum position i.e. to the bottom.
     */
    void scrollToBottom();

    /**
     * Scrolls the vertical scroll bar to its minimum position i.e. to the top.
     */
    void scrollToTop();

    /** Escapes " and \n  (for JS evaluation) */
    void escapeString(QString& str);

    /** Escapes " and \n  (for JS evaluation) [overload] */
    QString escapeStringCopy(QString str);
    
    /** Evaluates JavaScript code */
    void evaluateJS(QString scriptSource);

    /** Reads JavaScript code (function definitions) from resource file and evaluates it in webkit */
    void importJSChatFunctions();

    public
slots:

    /**
     * Ask user if \param url should be added to whiteList and then calls js:psi_unban(url) if user confirms.
     * 
     * It's used to display blocked images.
     */
    void onAddToWhiteListRequested(const QString& url);


protected:
    /** Creates menu with Copy actions */
    void contextMenuEvent(QContextMenuEvent* event);

    /** Handles icon:// URLs and disallows network requests */
    NetworkAccessManager *networkManager;

    QAction* copyAction, *copyLinkAction;
};


#endif

