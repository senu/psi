#ifndef HAVE_CHAT_VIEW
#define HAVE_CHAT_VIEW

#include <Qt> 
#include <QWidget> 

#include "chatEvent.h"

class ChatEvent;

/** Abstract ChatView widget */
class ChatView : public QWidget 
{
Q_OBJECT

  public:	
	ChatView(QWidget* parent) : QWidget(parent) {} 

	virtual void appendEvent(const ChatEvent* event) = 0;
	virtual void appendMessage(const MessageChatEvent* event) = 0;

	/** clears all messges */
	virtual void clear() = 0;
	
	virtual ~ChatView() {}	
};
#endif

