#ifndef HAVE_HTML_CHAT_VIEW
#define HAVE_HTML_CHAT_VIEW

#include <QWebView>
#include <QWebFrame>
#include <QFile>
#include <QtDebug>

#include "chatView.h"
#include "htmlChatTheme.h"

class ChatView;
class HTMLChatTheme;

/** Themable Webkit-based HTML Chat View */
class HTMLChatView : public ChatView {
    Q_OBJECT

public:
    HTMLChatView(QWidget * parent);

    ~HTMLChatView();
    QWebView webView;

public slots:
    void evaluateJS(QString scriptSource);

    /** Reads JavaScript code (function definitions) from file and evaluates it in webkit */
    void importJSChatFunctions();

    void clear();

    void appendMessage(const MessageChatEvent *msg);
    void appendEvent(const ChatEvent* event);

    /** Creates HTML document (header,chat,footer) */
    void init();

private slots:
	/** Load JS code, append header, chat div, and footer 
	    ok <=> document loaded successfully
	 */
	void onEmptyDocumentLoaded(bool ok);
	
	/** Creates html document with base href tag somewhere*/ //TODO avoid creating document
	void createEmptyDocument(QString baseHref);



private:
    /** Escapes " and \n  (for JS evaluation) */
    void escapeString(QString& str);
    HTMLChatTheme theme; // maybe HTMLChatTheme* to global theme - don't know






};

#endif