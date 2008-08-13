#ifndef HAVE_HTML_CHAT_VIEW
#define HAVE_HTML_CHAT_VIEW

#include <QWebView>
#include <QWebFrame>
#include <QFile>
#include <QtDebug>
#include <QPair>
#include <QRect>
#include <QVBoxLayout>

#include "chatView.h"
#include "htmlChatTheme.h"
#include "jsnotifier.h"
#include "networkaccessmanager.h"
#include "iconserver.h"

class ChatView;
class HTMLChatTheme;


/** 
 * Themable Webkit-based HTML Chat View 
 * 
 * NOTE: 1. QWebkit runs in separate thread (no matter how many instances of QWebView
 * NOTE:     you have - there always is one thread)
 * NOTE: 2. Because QWebkit runs in separate thread, and doesn't have DOM interface on C++ side
 * NOTE:    we need to synchronize IconServer, queue chat events and theme changes
 */
class HTMLChatView : public ChatView {

    Q_OBJECT

public:
    /** 
     * Constructor 
     *
     * \param iconServer will be passed to NetworkAccessManager
     * \param theme_ will be used as a ChatView theme
     */
    HTMLChatView(QWidget * parent, HTMLChatTheme theme_, IconServer* iconServer);

    ~HTMLChatView();

    /** Sets theme (if needed) */
    void setTheme(const HTMLChatTheme& theme);
    
    /** Creates HTML document (header,chat,footer) */
    void init();

    //reimplemented
    bool atBottom() const;
    bool internalFind(const QString& str, bool startFromBeginning = false);
    bool hasSelectedText() const;
    void copySelectedText();


    public


slots:
    /**
     * Scrolls the vertical scroll bar to its maximum position i.e. to the bottom.
     */
    void scrollToBottom();

    /**
     * Scrolls the vertical scroll bar to its minimum position i.e. to the top.
     */
    void scrollToTop();

    /** Evaluates JavaScript code in Webkit */
    void evaluateJS(QString scriptSource);

    /** Reads JavaScript code (function definitions) from file and evaluates it in webkit */
    void importJSChatFunctions();

    /** Appends message */
    void appendMessage(MessageChatEvent *msg, bool alreadyAppended = false);

    /** Appends event (filetransfer, mood, etc) */
    void appendEvent(ChatEvent* event, bool alreadyAppended = false);

    /** Returns HTML contained in webView */
    QString dumpContent();

    //reimplemented
    void setVisible(bool visible);
    QSize sizeHint() const;
    
    void clear();
    
    void scrollUp();
    void scrollDown();
    
    void updateTrackBar();

signals:
    void appendFinished();
    
    /** Emitted when user click on URL */
    void openURL(QString);

    private
slots:
    /** Load JS code, append header, chat div, and footer 
        ok <=> document loaded successfully
     */
    void onEmptyDocumentLoaded(bool ok);

    /** JS::psi_initDocument finished; Reappends events */
    void onInitDocumentFinished();

    /** 
     * JS::psi_append* finished 
     *
     * Scrolls to bottom if needed.
     */
    void onAppendFinished();

    /** Scrolls to the bottom of page */
    void onDoScrolling();

    /** Emits openURL() */
    void onLinkClicked(const QUrl& url);

    /** Creates html document with base href tag somewhere; themeVariant is without css suffix */ 
    QString createEmptyDocument(QString baseHref, QString themeVariant);
    
    /**
     * Ask user if \param url should be added to whiteList and then calls js:psi_unban(url) if user confims.
     * 
     * It's used to display blocked images.
     */
    void onAddToWhiteListRequested(const QString& url);

private:
    /** Escapes " and \n  (for JS evaluation) */
    void escapeString(QString& str);

    /** Escapes " and \n  (for JS evaluation) */
    QString escapeStringCopy(QString str);

    /** Creates menu with Copy action */
    void contextMenuEvent(QContextMenuEvent* event);

    /** Current theme */
    HTMLChatTheme theme;

    /** JavaScript - C++ bridge */
    JSNotifier jsNotifier;

    /** Handles icon:// URLs and disallwos network requests */
    NetworkAccessManager * networkManager;

    /** ChatView is ready to: change theme, append events (true after onInitDouemtet finished) */
    bool isReady;

    /** Theme changed while webkit was busy */
    HTMLChatTheme* queuedTheme;
    
    /** Someone tried to clear() ChatView before Webkit was ready to do that */
    bool queuedClear;

    QWebView webView;
    
    QVBoxLayout * layout;

};

#endif
