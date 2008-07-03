#include "htmlChatThemeList.h"
#include <QDir>
#include <QtDebug>
#include <QStringList>
#include <QString>

#include "config.h"

void HTMLChatThemeList::readThemes() {
	QString path=_THEMEPATH"themes";
	
	QDir dir(path);

	if(!dir.exists())
		throw (double)1;
	
	QStringList subdirs = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs); 
	QString subdir;
	
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

	if(!dir.exists())
		throw (long double)1;
	
	return dir.exists("Contents/Resources");
}
