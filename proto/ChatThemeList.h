#ifndef _CHATTHEMELIST_H
#define	_CHATTHEMELIST_H

#include <QList>
#include "ChatTheme.h"

class ChatThemeList : public QList<ChatTheme*> {
	
	virtual void readThemes();

};


#endif

