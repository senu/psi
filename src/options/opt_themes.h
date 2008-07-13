#ifndef _OPT_THEMES_H
#define	_OPT_THEMES_H

#include "optionstab.h"
#include "../htmlChatThemeList.h"

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


private:
    QWidget *w, *parentWidget;
    PsiCon *psi;

};

#endif

