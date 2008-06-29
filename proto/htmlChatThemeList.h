#ifndef _HTMLCHATTHEMELIST_H
#define	_HTMLCHATTHEMELIST_H

#include "chatThemeList.h"

class HTMLChatThemeList : public ChatThemeList {
public:	
	//reimplemented
	void readThemes();
	
	virtual bool validateTheme(QString themeFolder); 
	
};


#endif	

