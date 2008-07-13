#include "opt_themes.h"
#include "ui_opt_themes.h"


class OptThemeUI : public QWidget, public Ui::OptTheme {

public:


    OptThemeUI() : QWidget() {
        setupUi(this);
    }
};


OptionsTabThemes::OptionsTabThemes(QObject *parent)
: OptionsTab(parent, "themes", "", tr("Themes"), tr("Configure how Psi themes"), "psi/playSound") {//TODO icon
    w = 0;
}


OptionsTabThemes::~OptionsTabThemes() {
}


QWidget *OptionsTabThemes::widget() {
    if (w)
        return 0;

    w = new OptThemeUI();
    OptThemeUI *d = (OptThemeUI *) w;


    HTMLChatThemeList themeList;
    themeList.readThemes("/home/senu/dev/psi/gsoc/repo/psi-fork/src"); //TODO

    d->themeCB->addItems(themeList.themeNames());

    /*
        QWhatsThis::add(d->,
                        tr("If your system supports multiple sound players, you may"
                           " choose your preferred sound player application here."));
        QWhatsThis::add(d->ck_awayTheme,
                        tr("Enable this option if you wish to hear sound alerts when your status is \"away\" or \"extended away\"."));
        QWhatsThis::add(d->ck_gcTheme,
                        tr("Play sounds for all events in groupchat, not only for mentioning of your nick."));
     */

    return w;
}


void OptionsTabThemes::applyOptions() {
    if (!w)
        return;

    OptThemeUI *d = (OptThemeUI *) w;
    //    PsiOptions::instance()->setOption("options.ui.themes.htmlviewinmuc", d->->text());
    //  PsiOptions::instance()->setOption("options.ui.notifications.sounds.silent-while-away", !d->ck_awayTheme->isChecked());
}


void OptionsTabThemes::restoreOptions() {
    if (!w)
        return;

    OptThemeUI *d = (OptThemeUI *) w;

    //    d->ck_awayTheme->setChecked(!PsiOptions::instance()->getOption("options.ui.notifications.sounds.silent-while-away").toBool());
    //   d->ck_gcTheme->setChecked(PsiOptions::instance()->getOption("options.ui.notifications.sounds.notify-every-muc-message").toBool());
}


void OptionsTabThemes::setData(PsiCon *, QWidget *p) {
    parentWidget = p;
}
