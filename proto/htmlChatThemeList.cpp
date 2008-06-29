#include "htmlChatThemeList.h"
#include <QDir>
#include <QtDebug>
#include <QStringList>
#include <qt4/QtCore/qstring.h>

void HTMLChatThemeList::readThemes() {
#warning change next line	
	QString path="/home/senu/dev/psi/gsoc/repo/psi-fork/proto/themes";
	
	QDir dir(path);

	if(!dir.exists())
		throw (double)1;
	
	QStringList subdirs = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs); 
	QString subdir;
	
	foreach(subdir, subdirs) {
		qDebug() << subdir;
		if (validateTheme(dir.absoluteFilePath(subdir))) {
			qDebug() << subdir;
			themeDict[generateThemeName(subdir)]=dir.absoluteFilePath(subdir);
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