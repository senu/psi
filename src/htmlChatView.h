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

class ChatView;
class HTMLChatTheme;


/** Themable Webkit-based HTML Chat View */
class HTMLChatView : public ChatView {

    Q_OBJECT

public:
    HTMLChatView(QWidget * parent, HTMLChatTheme theme, QString themePath);

    ~HTMLChatView();
    QWebView webView;

    /** Sets theme */
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

    void evaluateJS(QString scriptSource);

    /** Reads JavaScript code (function definitions) from file and evaluates it in webkit */
    void importJSChatFunctions();

    void clear();

    /** Appends message */
    void appendMessage(const MessageChatEvent *msg, bool alreadyAppended = false);

    /** Appends event (filetransfer, mood, etc) */
    void appendEvent(const ChatEvent* event, bool alreadyAppended = false);

    /** Returns HTML contained in webView */
    QString dumpContent();

    //reimplemented
    void setVisible(bool visible);
    void setChatInfo(ChatTheme::ChatInfo chatInfo);
    ChatTheme::ChatInfo chatInfo() const;

signals:
    void appendFinished();

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

    /** Opens URL in a new window */
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

    QVBoxLayout * layout;

};

#endif
