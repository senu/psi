#include "htmlChatThemeList.h"
#include <QDir>
#include <QtDebug>
#include <QStringList>
#include <QString>


void HTMLChatThemeList::readThemes(const QString& _path) {
    QString path = _path;
    if (!path.endsWith("/")) {
        path = path + "/";
    }
	if (!path.endsWith("themes/")) { //TODO 104
	    path = path + "themes/";
    }
	
	QDir dir(path);

    if(!dir.exists()) {
        themeDict.clear();
        qDebug() << "WARNING: HTMLChatThemeList::readThemes() theme dir doesn't exist";
        return;
    }
	
	QStringList subdirs = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs); 
	QString subdir;

    themeDict.clear();
	foreach(subdir, subdirs) {
		if (validateTheme(dir.absoluteFilePath(subdir))) {
			themeDict[generateThemeName(subdir)]=dir.absoluteFilePath(subdir+"/");
		}
	}
}

bool HTMLChatThemeList::validateTheme(QString themePath) {
	if (!ChatThemeList::validateTheme(themePath))
		return false;
	
	QDir dir(themePath);

    return dir.exists("Contents/Resources");
}
