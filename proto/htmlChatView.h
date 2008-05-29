#ifndef HAVE_HTML_CHAT_VIEW
#define HAVE_HTML_CHAT_VIEW

#include <QWebView>
#include <QWebFrame>

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
	}

	~HTMLChatView() {}

  public slots:
	void evaluateJS(QString scriptSource) {
		webView.page()->mainFrame()->evaluateJavaScript(scriptSource);
		qDebug ("HTMLChatView::evaluateJS()");
	}

	void importJSChatFunctions() {
	
	}
	void evaluateJS() {			
		evaluateJS("function x() {document.getElementById('senu').innerHTML='yyy';} x();");
	}


  private:
	HTMLChatTheme theme; // maybe HTMLChatTheme* to global theme - don't know

	QWebView webView; 


	void appendEvent(const ChatEvent& event) {
		QString part = event.getRightTemplateAndFillItWithData(theme);

		//findPlaceForNewEventAndInsert(part); 			
		//scrolling, misc. 
	}


};

#endif
