#ifndef HAVE_CHAT_VIEW
#define HAVE_CHAT_VIEW

#include <Qt> 
#include <QWidget> 

class ChatEvent;

class ChatView : public QWidget 
{
Q_OBJECT

  public:	
	ChatView(QWidget* Parent); 

	virtual void appendEvent(const ChatEvent& event) = 0;

	/** clears all messges */
	virtual void clear() = 0;
	
	virtual ~ChatView() {}	
};
#endif

