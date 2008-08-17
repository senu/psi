#ifndef _HTMLTHEMEMANAGER_H
#define	_HTMLTHEMEMANAGER_H

#include <QString>
#include <QHash>
#include <QPair>

#include "htmlchatthemelist.h"
#include "htmlchattheme.h"


/**
 * Stores HTMLThemeList and caches loaded (from filesystem) themes.
 */
class HTMLThemeManager {

public:
    /**
     * Fills the theme list with themes located in themesDir dir. 
     */
    HTMLThemeManager(const QString& themesDir);
    ~HTMLThemeManager();

    /** 
     * Returns theme list. 
     * 
     * It is used in PsiOptions 
     */
    const HTMLChatThemeList* themeList() const;

    /** 
     * Returns theme and loads it from filesystem if needed.
     *
     * Use theme.isValid() after this call.
     */
    HTMLChatTheme getTheme(const QString& themeName, const QString& variant);
    
private:
    HTMLChatThemeList * themeList_;

    /** Loaded themes [(path,variant) -> theme] */
    QHash< QPair<QString, QString>, HTMLChatTheme> themeCache;

    /** A path to dir with themes */
    QString themesDir;
};

#endif

