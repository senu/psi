#ifndef _CHATTHEMELIST_H
#define	_CHATTHEMELIST_H

#include <QList>
#include "chatTheme.h"

class ChatThemeList : public QList<ChatTheme*> {
	
	virtual void readThemes();

};


#endif

