#include "htmlthememanager.h"
#include "applicationinfo.h"


HTMLThemeManager::HTMLThemeManager() {

    _themeList = new HTMLChatThemeList();
    _themeList->readThemes(ApplicationInfo::homeDir()); //TODO 61 move up decouple
}


HTMLThemeManager::~HTMLThemeManager() {
    delete _themeList;
}


const HTMLChatThemeList* HTMLThemeManager::themeList() const {
    return _themeList;
}


HTMLChatTheme HTMLThemeManager::getTheme(const QString& themeName, const QString& variant) {

    QString path = _themeList->themePath(themeName);

    if (path.isEmpty()) { //theme not found, but filesystem could be changed since last check
        _themeList->readThemes(ApplicationInfo::homeDir());
        path = _themeList->themePath(themeName);
    }

    if (!path.isEmpty()) { //theme found
        QPair<QString, QString> key(path, variant);

        if (_themeCache.contains(key)) {
            return _themeCache[key];
        }

        //cache miss
        HTMLChatTheme theme(path);
        theme.setCurrentVariant(variant);
        _themeCache.insert(key, theme);
        return theme;
    }

    return HTMLChatTheme(); //empty theme is not valid() theme
}