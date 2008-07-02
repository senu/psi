#ifndef HAVE_HTML_CHAT_PART
#define HAVE_HTML_CHAT_PART

#include <QString>
#include <QtDebug>
#include <QDateTime> 

/** Part (string) of HTMLChat document (eg. newly created message/event)
 *
 * 	+ method to escape and replace %keywords% with corresponding values
 */
class HTMLChatPart {
  public:

	HTMLChatPart() {};

	/** Creates HTMLChatPart with body = content*/
	HTMLChatPart(const QString _content); 

	/** Replaces occurence of %keyword% with escaped value */
	void replaceAndEscapeKeyword(QString keyword, QString value); 
	
	/** Replaces occurence of %message% with escaped value;
	 *  We need this method because user input must be validated by CSS validator  
	 *  written in JS.
	 */
	void replaceMessageBody(QString value);  //TODO unused

	/** Replaces %keyword% with value */
	void replaceKeyword(QString keyword, QString value); 
	
	/** Replaces time keyword %keyword{format}% with formatted time */
	void replaceTimeKeyword(QString keyword, QDateTime time); 

	/** Escapes string */
	static QString escapeString(QString string); //TODO unused

	/** Converts part to string */
	QString toString();

	/** Returns value of %message% */
	QString messageBody() const;

  private:
	/** Part body */
	QString content;

	/** Message body (%message%) */ //TODO create new class (footer/header/event and message)
	QString _messageBody;
	
	/** Returns formated time, eg for %timeOpened{X}% */
	QString formatTime(QString format, QDateTime time);
};

#endif
