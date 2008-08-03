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


/** Themable Webkit-based HTML Chat View */
class HTMLChatView : public ChatView {

    Q_OBJECT

public:
    /** 
     * Constructor 
     *
     * \param iconServer will be passed to NetworkAccessManager
     * \param theme_ will be used as a ChatView theme
     */
    HTMLChatView(QWidget * parent, HTMLChatTheme theme_, IconServer* iconServer, QString _themePath);

    ~HTMLChatView();

    /** Sets theme (if needed) */
    void setTheme(HTMLChatTheme theme);

    /** Only in dev version; (only for loading JavaScript file); path to theme/ dir */
    QString themePath;
    
    /** Creates HTML document (header,chat,footer) */
    void init();

    //reimplemented
    bool atBottom() const;


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
    void appendMessage(const MessageChatEvent *msg, bool alreadyAppended = false);

    /** Appends event (filetransfer, mood, etc) */
    void appendEvent(const ChatEvent* event, bool alreadyAppended = false);

    /** Returns HTML contained in webView */
    QString dumpContent();

    //reimplemented
    void setVisible(bool visible);
    QSize sizeHint() const;
    void clear();
    void scrollUp();
    void scrollDown();

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

    /** JS::psi_append* finished */
    void onAppendFinished();

    /** Scrolls to the bottom of page */
    void onDoScrolling();

    /** Emits openURL() */
    void onLinkClicked(const QUrl& url);

    /** Creates html document with base href tag somewhere; themeVariant is without css suffix */ //TODO avoid creating document
    QString createEmptyDocument(QString baseHref, QString themeVariant);

private:
    
    /** Escapes " and \n  (for JS evaluation) */
    void escapeString(QString& str);

    /** Escapes " and \n  (for JS evaluation) */
    QString escapeStringCopy(QString str);

    /** Current theme */
    HTMLChatTheme theme;

    /** JavaScript - C++ bridge */
    JSNotifier jsNotifier;

    /** Handles icon:// URLs and disallwos network requests */
    NetworkAccessManager * networkManager;

    /** ChatView is ready to: change theme, append events (after onInitDouemtet finished) */
    bool isReady;

    //TODO queued actions (things we got while webkit was initializatin empty chat)
    /** Theme changed */
    HTMLChatTheme* queuedTheme;

    QWebView webView;
    
    QVBoxLayout * layout;

};

#endif
