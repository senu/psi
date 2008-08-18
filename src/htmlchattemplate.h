#ifndef _HTMLCHATTEMPLATE_H
#define	_HTMLCHATTEMPLATE_H

#include <Qt>

#include "htmlchatpart.h"

/** 
 * Message/Event template 
 * 
 * It's QString + loading methods.
 */
class HTMLChatTemplate {

public:

	/** Creates HTMLChatTemplate with content as content*/
	HTMLChatTemplate(const QString content);
    HTMLChatTemplate(const HTMLChatTemplate& other);
	
	HTMLChatTemplate() {};

	QString content() const;
	void setContent(QString);

	/** Creates new HTMLChatPart */
	HTMLChatPart createFreshHTMLPart() const;

private:
	/** Template body */
	QString content_;

};

#endif
