#ifndef HAVE_TEST_FORM
#define HAVE_TEST_FORM

#include <Qt> 
#include <QWidget> 
#include <QComboBox> 
#include <QFrame> 
#include <QLineEdit>

#include "messagechatevent.h"
#include "htmlChatThemeList.h"
#include "htmlChatView.h"
#include "htmlchateditframe.h"
#include "messageValidator.h"


/** Form that holds ChatView widget */
class TestForm : public QFrame {
Q_OBJECT    

  public:
    TestForm(QWidget * parent);
	~TestForm();			
  private:
    QLineEdit * themePathEdit;
    HTMLChatEditFrame * frame;
	QComboBox *themeComboBox;
	QComboBox *variantComboBox;

	HTMLChatView * view;
	HTMLChatTheme * theme;
	HTMLChatThemeList themeList;
	MessageValidator msgVal; 

  private slots:
    /** creates message */
    void onConsecutiveButtonClicked();
    void onNextButtonClicked();
    void onEventButtonClicked();
	void onLoadTheme();
	void onLoadVariant();
	void onClear();
	void onRunTests();

  signals:      
    /** on message created */
    void messageCreated(const MessageChatEvent*);        
    void eventCreated(const ChatEvent*);        
};

#endif


