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
	if (!path.endsWith("themes/")) {
	    path = path + "themes/";
    }
	
	QDir dir(path);

	if(!dir.exists())
		throw (double)1;
	
	QStringList subdirs = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs); 
	QString subdir;

    themeDict.clear();
	foreach(subdir, subdirs) {
//		qDebug() << subdir;
		if (validateTheme(dir.absoluteFilePath(subdir))) {
//			qDebug() << subdir;
			themeDict[generateThemeName(subdir)]=dir.absoluteFilePath(subdir+"/");
		}
	}
}

bool HTMLChatThemeList::validateTheme(QString themePath) {
	if (!ChatThemeList::validateTheme(themePath))
		return false;
	
	QDir dir(themePath);

    if(!dir.exists()) {
		throw (long double)1; //TODO 9
    }

    return dir.exists("Contents/Resources");
}
