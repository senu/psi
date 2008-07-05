#ifndef HAVE_HTML_CHAT_VIEW
#define HAVE_HTML_CHAT_VIEW

#include <QWebView>
#include <QWebFrame>
#include <QFile>
#include <QtDebug>
#include <QPair>
#include <QList>
#include <QRect>

#include "chatView.h"
#include "htmlChatTheme.h"
#include "jsnotifier.h"

class ChatView;
class HTMLChatTheme;


/** Themable Webkit-based HTML Chat View */
class HTMLChatView : public ChatView {

    Q_OBJECT

public:
    HTMLChatView(QWidget * parent, HTMLChatTheme theme);

    ~HTMLChatView();
    QWebView webView;

    /** Sets theme */
    void setTheme(HTMLChatTheme theme);


    public
slots:
    void evaluateJS(QString scriptSource);

    /** Reads JavaScript code (function definitions) from file and evaluates it in webkit */
    void importJSChatFunctions();

    void clear();

    /** Appends message */
    void appendMessage(const MessageChatEvent *msg);

    /** Appends event (filetransfer, mood, etc) */
    void appendEvent(const ChatEvent* event);

    /** Creates HTML document (header,chat,footer) */
    void init();

    /** Returns HTML contained in webView */
    QString dumpContent();

    //reimplemented
    void setVisible(bool visible);
    void setChatInfo(ChatTheme::ChatInfo chatInfo);
    ChatTheme::ChatInfo chatInfo() const;

signals:
    void appendFinished();
    void initDocumentFinished();

    private
slots:
    /** Load JS code, append header, chat div, and footer 
        ok <=> document loaded successfully
     */
    void onEmptyDocumentLoaded(bool ok);

    /** JS::psi_initDocument finished */
    void onInitDocumentFinished();

    /** JS::psi_append* finished */
    void onAppendFinished();

    void onDupa(QRect geom);

    /** Creates html document with base href tag somewhere; themeVariant is without css suffix */ //TODO avoid creating document
    QString createEmptyDocument(QString baseHref, QString themeVariant);


private:
    /** Escapes " and \n  (for JS evaluation) */
    void escapeString(QString& str);

    /** Escapes " and \n  (for JS evaluation) */
    QString escapeStringCopy(QString str);

    /** Appends message, if alreadyAppended we won't add it to appendedEvents */
    void appendMessage(const MessageChatEvent *msg, bool alreadyAppended);

    /** Appends event, if alreadyAppended we won't add it to appendedEvents */
    void appendEvent(const ChatEvent* event, bool alreadyAppended);


    HTMLChatTheme theme; // maybe HTMLChatTheme* to global theme - don't know

    /** Session info */
    ChatTheme::ChatInfo _chatInfo;

    /* Appended events - we need to remember it in case of theme change */
    QList <const AbstractChatEvent*> appendedEvents;

    /** JavaScript - C++ bridge */
    JSNotifier jsNotifier;

};

#endif
