#include "htmlthememanager.h"
#include "applicationinfo.h"


HTMLThemeManager::HTMLThemeManager() {

    _themeList = new HTMLChatThemeList();
    _themeList->readThemes(ApplicationInfo::homeDir()); //TODO decouple
}


HTMLThemeManager::~HTMLThemeManager() {
    delete _themeList;
}


const HTMLChatThemeList* HTMLThemeManager::themeList() const {
    return _themeList;
}


HTMLChatTheme HTMLThemeManager::getTheme(QString themeName) {
    
    QString path = _themeList->themePath(themeName);

    if (path.isEmpty()) { //theme not found, but we filesystem could be changed
        _themeList->readThemes(ApplicationInfo::homeDir());
        path = _themeList->themePath(themeName);
    }

    if (!path.isEmpty()) { //theme in list
        if (_themeCache.contains(path)) {
            return _themeCache[path];
        }

        //cache miss
        HTMLChatTheme theme(path); //TODO ? pointers/refs insead of copying
        _themeCache.insert(path, theme);
        return theme;
    }

    return HTMLChatTheme(); //empty theme is not valid() theme
}