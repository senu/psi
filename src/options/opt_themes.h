#ifndef _OPT_THEMES_H
#define	_OPT_THEMES_H

#include "optionstab.h"
#include "../htmlChatThemeList.h"
#include "../htmlChatTheme.h"

/** Options tab where user can set theme/ChatView */
class OptionsTabThemes : public OptionsTab {

    Q_OBJECT
public:

    OptionsTabThemes(QObject *parent);
    ~OptionsTabThemes();

    QWidget *widget();
    void applyOptions();
    void restoreOptions();

    private
slots:
    void setData(PsiCon *, QWidget *);
            
    /** \param themeIndex is chosen theme index in the combobox */
    void onThemeLoaded(int themeIndex);

    /** \param themeIndex is chosen variant index in the combobox */
    void onVariantLoaded(int variantIndex);


private:
    QWidget *w, *parentWidget;
    PsiCon *psi;
    HTMLChatThemeList themeList;
    HTMLChatTheme * theme;

};

#endif

