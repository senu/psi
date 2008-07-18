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
    /** Loads theme list */
    HTMLThemeManager();
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
    QHash<QPair<QString,QString>, HTMLChatTheme> _themeCache;
    

};

#endif
