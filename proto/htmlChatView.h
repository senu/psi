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
	void evaluateJS(QString scriptSource) {
		webView.page()->mainFrame()->evaluateJavaScript(scriptSource);
		qDebug ("HTMLChatView::evaluateJS()");
	}

  	/** Reads JavaScript code (function definitions) from file and evaluates it in webkit */
	void importJSChatFunctions() {
		// reading from file only while developing	
		QFile file("htmlChatView.js");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	         return;

		QString jsCode = file.readAll();

		evaluateJS(jsCode);

	}

	void evaluateJS() {			
		evaluateJS("x()");
	}

	void clear();

	//for testing purposes only
	void appendNextMessage();
//	void appendConsecutiveMessage();
	void appendConsecutiveMessage__(const MessageChatEvent * msg);


  private:
	HTMLChatTheme theme; // maybe HTMLChatTheme* to global theme - don't know

	void appendEvent(const ChatEvent& event);



};

#endif
