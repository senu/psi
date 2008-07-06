#ifndef _HTMLCHATTHEMELIST_H
#define	_HTMLCHATTHEMELIST_H

#include "chatThemeList.h"

/** List of HTMLChatTheme names; eg for selecting theme */
class HTMLChatThemeList : public ChatThemeList {
public:	
	//reimplemented
    /** Path to themes/ dir */
	void readThemes(const QString& themesPath);
	
	virtual bool validateTheme(QString themeFolder); 
	
};


#endif	

