#ifndef _HTMLCHATTHEMELIST_H
#define	_HTMLCHATTHEMELIST_H

#include "chatThemeList.h"

/** List of HTMLChatTheme names; eg for selecting theme */
class HTMLChatThemeList : public ChatThemeList {
public:	
	//reimplemented
	void readThemes();
	
	virtual bool validateTheme(QString themeFolder); 
	
};


#endif	

