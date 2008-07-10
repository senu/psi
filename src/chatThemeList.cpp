#include <QHash>
#include "chatThemeList.h"


QStringList ChatThemeList::themeNames() {
    return themeDict.keys();
}


QString ChatThemeList::themePath(QString themeName) {
    return themeDict[themeName];
}


bool ChatThemeList::validateTheme(QString themePath) {
    return true;
}


QString ChatThemeList::generateThemeName(QString themeFolder) {

    themeFolder = themeFolder.left(themeFolder.indexOf('.', 0, Qt::CaseInsensitive));

    if (!themeDict.contains(themeFolder))
        return themeFolder;

    for (int i = 2; i <= 1 << 30; i++) { //TODO ask kev
        if (!themeDict.contains(themeFolder + QString::number(i)))
            return themeFolder + QString::number(i);
    }
}
