#ifndef _HTMLTHEMEMANAGER_H
#define	_HTMLTHEMEMANAGER_H

#include <QString>
#include <QHash>
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
    HTMLChatTheme getTheme(QString themeName);
private:
    HTMLChatThemeList * _themeList;
    
    /** Loaded themes [path -> theme] */
    QHash<QString, HTMLChatTheme> _themeCache;
    

};

#endif

