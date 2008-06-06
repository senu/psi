#include <Qt>
#include <QString>

//TODO change name
/** Message/Event template */
class HTMLChatTemplate {

public:

	/** Creates HTMLChatTemplate with content as content*/
	HTMLChatTemplate(QString content);
	HTMLChatTemplate() {};

	/** Replaces occurence of %keyword% with escaped value */
	void replaceAndEscapeKeyword(QString keyword, QString value); 

	/** Replaces %keyword% with value */
	void replaceKeyword(QString keyword, QString value); 

	/** Escapes string */
	void escapeString(QString string); 

	/** Converts template to string */
	QString toString();

private:
	/** Template body */
	QString content;

};
