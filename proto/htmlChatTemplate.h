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

	/** Creates new HTMLChatPart */
	HTMLChatPart createFreshHTMLPart();

private:
	/** Template body */
	QString content;

};
