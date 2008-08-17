#include "htmlthememanager.h"
#include "applicationinfo.h"


HTMLThemeManager::HTMLThemeManager(const QString& themesDir_) : themesDir(themesDir_) {

    themeList_ = new HTMLChatThemeList();
    themeList_->readThemes(QDir(themesDir));
}


HTMLThemeManager::~HTMLThemeManager() {
    delete themeList_;
}


const HTMLChatThemeList* HTMLThemeManager::themeList() const {
    return themeList_;
}


HTMLChatTheme HTMLThemeManager::getTheme(const QString& themeName, const QString& variant) {

    QString path = themeList_->themePath(themeName);

    if (path.isEmpty()) { //theme not found, but filesystem could have been changed since last check
        themeList_->readThemes(QDir(themesDir));
        path = themeList_->themePath(themeName);
    }

    if (!path.isEmpty()) { //theme found
        QPair<QString, QString> key(path, variant);

        if (themeCache.contains(key)) {
            return themeCache[key];
        }

        //cache miss
        HTMLChatTheme theme(path);
        theme.setCurrentVariant(variant);
        themeCache.insert(key, theme);
        return theme;
    }

    return HTMLChatTheme(); //empty theme is not valid() theme
}
