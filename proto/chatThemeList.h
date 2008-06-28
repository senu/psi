#ifndef _CHATTHEMELIST_H
#define	_CHATTHEMELIST_H

#include <QHash>
#include <QString>
#include <QStringList>
#include "chatTheme.h"

/** Abstract List of theme names; eg. for selecting theme 
 *
 *  TODO:
 *  Pro and Pro.AdiumMessageStyle name conflicts
 *  validate theme
 *
 */

class ChatThemeList {
public:	
	virtual void readThemes() = 0;
	QStringList themeNames();
	QString themePath(QString themeName);
	
protected:
	/** Checks if themeFolder contains valid theme */
	virtual bool validateTheme(QString themeFolder); //TODO implement it
	
	/** Generates theme name for theme in themeFolder */
	virtual QString generateThemeName(QString themePath);

	/** Theme name -> theme path dictionary */
	QHash<QString, QString> themeDict;
	

};


#endif

