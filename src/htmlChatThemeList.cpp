#include "htmlChatThemeList.h"
#include <QDir>
#include <QtDebug>
#include <QStringList>
#include <QString>


void HTMLChatThemeList::readThemes(const QDir& themesDir) {

    themeDict.clear();
    
    if(!themesDir.exists()) {
        qDebug() << "WARNING: HTMLChatThemeList::readThemes() theme dir doesn't exist";
        return;
    }
	
	QStringList subdirs = themesDir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs); 
	QString subdir;

    qDebug() << themesDir << subdirs;

	foreach(subdir, subdirs) {
		if (validateTheme(themesDir.absoluteFilePath(subdir))) {
			themeDict[generateThemeName(subdir)]=themesDir.absoluteFilePath(subdir+"/");
		}
	}
}

bool HTMLChatThemeList::validateTheme(QString themePath) {
	if (!ChatThemeList::validateTheme(themePath))
		return false;
	
	QDir dir(themePath);

    return dir.exists("Contents/Resources");
}
