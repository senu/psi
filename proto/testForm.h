#ifndef HAVE_TEST_FORM
#define HAVE_TEST_FORM

#include <Qt> 
#include <QWidget> 
#include <QComboBox> 
#include <QFrame> 
#include <QLineEdit>

#include "chatMessageEvent.h"
#include "htmlChatThemeList.h"
#include "htmlChatView.h"


/** Form that holds ChatView widget */
class TestForm : public QFrame {
Q_OBJECT    

  public:
    TestForm(QWidget * parent);
    ~TestForm(); //TODO

  private:
    QLineEdit * messageEdit;
	QComboBox *comboBox;

	HTMLChatView * view;
	HTMLChatThemeList themeList;

  private slots:
    /** creates message */
    void onConsecutiveButtonClicked();
    void onNextButtonClicked();
    void onEventButtonClicked();

  signals:      
    /** on message created */
    void messageCreated(const MessageChatEvent*);        
    void eventCreated(const ChatEvent*);        
};

#endif

