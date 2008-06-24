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

class HTMLChatView : public ChatView 
{
	Q_OBJECT

  public:
	HTMLChatView(QWidget * parent) : ChatView(parent) {
		webView.setParent(parent);

		importJSChatFunctions();
	}

	~HTMLChatView();
	QWebView webView; 

  public slots:
	void evaluateJS(QString scriptSource);

  	/** Reads JavaScript code (function definitions) from file and evaluates it in webkit */
	void importJSChatFunctions();

	void clear();

	void appendMessage(const MessageChatEvent *msg);


  private:
	HTMLChatTheme theme; // maybe HTMLChatTheme* to global theme - don't know

	void appendEvent(const ChatEvent& event);



};

#endif
