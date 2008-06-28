#include "chatThemeList.h"


QStringList ChatThemeList::themeNames() {
	return themeDict.keys(); 
}


QString ChatThemeList::themePath(QString themeName) {
	return themeDict[themeName]; 
}


bool ChatThemeList::validateTheme(QString themePath) {
//	if(themeFolder != "." && thmemF)
    return true; //TODO
}

QString ChatThemeList::generateThemeName(QString themeFolder) {
    return themeFolder; //TODO
}
