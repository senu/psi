#include <Qt>

#include "htmlChatPart.h"

//TODO change name
/** Message/Event template 
 * 
 *  It's QString + loading methods.
 */
class HTMLChatTemplate {

public:

	/** Creates HTMLChatTemplate with content as content*/
	HTMLChatTemplate(const QString content);
	
	HTMLChatTemplate() {};

	QString content() const;
	void setContent(QString);

	/** Creates new HTMLChatPart */
	HTMLChatPart createFreshHTMLPart() const;

private:
	/** Template body */
	QString _content;

};
