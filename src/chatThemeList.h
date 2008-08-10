#ifndef _CHATTHEMELIST_H
#define	_CHATTHEMELIST_H

#include <QHash>
#include <QString>
#include <QDir>
#include <QStringList>
#include "chatTheme.h"

/** Abstract List of theme names; eg for selecting theme */
class ChatThemeList {
public:	
    
    /** Reads themes from themesDir/ */
	virtual void readThemes(const QDir& themesDir) = 0;
	QStringList themeNames();
	QString themePath(QString themeName);
	
protected:
	/** 
     * Checks if themeFolder contains valid theme.  
     * Default implementation returns true.
     */
	virtual bool validateTheme(QString themeFolder);
	
	/** Generates theme name for theme in themeFolder */
	virtual QString generateThemeName(QString themePath);

	/** Theme name -> theme path dictionary */
	QHash<QString, QString> themeDict;
	

};


#endif

