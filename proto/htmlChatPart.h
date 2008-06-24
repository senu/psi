#ifndef HAVE_HTML_CHAT_PART
#define HAVE_HTML_CHAT_PART

#include <QString>
#include <QtDebug>

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

	/** Replaces %keyword% with value */
	void replaceKeyword(QString keyword, QString value); 

	/** Escapes string */
	QString escapeString(QString string); 

	/** Converts part to string */
	QString toString();

  private:
	/* Part body */
	QString content;
};

#endif
