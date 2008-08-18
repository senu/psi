#ifndef _HTMLCHATEMOTETEMPLATE_H
#define	_HTMLCHATEMOTETEMPLATE_H

#include "htmlchattemplate.h"

/** 
 * Emote (Action) template.
 * 
 * Action template is a Kopete extension. 
 * We must handle Adium themes in different way i.e. Adium Status.html tempalte doesn't
 * have %sender% keyword, so we must convert '/me message' to 'nick message'.
 */
class HTMLChatEmoteTemplate : public HTMLChatTemplate {

public:

	HTMLChatEmoteTemplate();
	HTMLChatEmoteTemplate(QString content);
	
	/** This value holds wheter EmoteTemplate was read from Action.html (if true - it's Kopete extenstion) */
	bool isEmoteTemplate() const;
	void setEmoteTemplate(bool is);
	
private:
	bool isEmoteTemplate_;

};

#endif	

