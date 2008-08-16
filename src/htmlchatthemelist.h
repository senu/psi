#ifndef _HTMLCHATTHEMELIST_H
#define	_HTMLCHATTHEMELIST_H

#include "chatthemelist.h"

/** List of HTMLChatTheme names; eg for selecting theme */
class HTMLChatThemeList : public ChatThemeList {
public:	
	//reimplemented
    /** Reads themes from themesDir */
	void readThemes(const QDir& themesDir);

protected:	
	bool validateTheme(QString themeFolder); 
	
};


#endif	

