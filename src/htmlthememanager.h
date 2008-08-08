#ifndef _HTMLTHEMEMANAGER_H
#define	_HTMLTHEMEMANAGER_H

#include <QString>
#include <QHash>
#include <QPair>
#include "htmlChatThemeList.h"
#include "htmlChatTheme.h"


/** Keeps HTML theme list, and caches loaded themes */
class HTMLThemeManager {

public:
    /**
     * Fils theme list with themes located in themesDir dir. 
     */
    HTMLThemeManager(const QString& themesDir);
    ~HTMLThemeManager();

    /** Returns theme list. Used in PsiOptions */
    const HTMLChatThemeList* themeList() const;

    /** 
     * Returns theme and loads it from filesystem if needed.
     * use theme.isValid() after this call
     */
    HTMLChatTheme getTheme(const QString& themeName, const QString& variant);
private:
    HTMLChatThemeList * _themeList;

    /** Loaded themes [(path,variant) -> theme] */
    QHash< QPair<QString, QString>, HTMLChatTheme> _themeCache;

    /** A path to dir with themes */
    QString themesDir;


};

#endif

