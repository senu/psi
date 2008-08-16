#ifndef _HTMLCHATEMOTETEMPLATE_H
#define	_HTMLCHATEMOTETEMPLATE_H

#include "htmlchattemplate.h"

/** Emote (Action) template is a Kopete extension. We must handle Adium themes in different way */
class HTMLChatEmoteTemplate : public HTMLChatTemplate {

public:

	HTMLChatEmoteTemplate() : HTMLChatTemplate(), _isEmoteTemplate(false) {};
	HTMLChatEmoteTemplate(QString content) : HTMLChatTemplate(content), _isEmoteTemplate(false) {};
	
	/** False if it wasn't created from Action.html */
	bool isEmoteTemplate() const;
	void setEmoteTemplate(bool is);
	
private:
	bool _isEmoteTemplate;

};

#endif	

