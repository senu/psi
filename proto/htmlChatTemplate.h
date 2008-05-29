#include <Qt>
class HTMLChatTemplate {

public:

	/** Replaces occurence of %keyword% with escaped value */
	void replaceAndEscapeKeyword(QString keyword, QString value); 

	/** Replaces %keyword% with value */
	void replaceKeyword(QString keyword, QString value); 

	/** Escapes string */
	void escapeString(QString string); 

	/** Converts template to string */
	QString toString();

private:
	/** template body */
	QString contents;

};
