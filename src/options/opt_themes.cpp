#include <QDebug>

#include "opt_themes.h"
#include "applicationinfo.h"
#include "psioptions.h"
#include "ui_opt_themes.h"

#include "iconset.h"


class OptThemeUI : public QWidget, public Ui::OptTheme {

public:


    OptThemeUI() : QWidget() {
        setupUi(this);
    }
};


OptionsTabThemes::OptionsTabThemes(QObject *parent)
: OptionsTab(parent, "themes", "", tr("Themes"), tr("Configure Psi themes"), "psi/playSound") {//TODO + 70 icon
    w = 0;
    theme = 0;
}


OptionsTabThemes::~OptionsTabThemes() {
    delete theme;
}


QWidget* OptionsTabThemes::widget() {
    if (w) {
        return 0;
    }

    w = new OptThemeUI();
    OptThemeUI *d = (OptThemeUI *) w;

    connect(d->themeCB, SIGNAL(currentIndexChanged(int)), this, SLOT(onThemeLoaded(int)));
    connect(d->variantCB, SIGNAL(currentIndexChanged(int)), this, SLOT(onVariantLoaded(int)));

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


void OptionsTabThemes::onThemeLoaded(int themeIndex) {

    if (themeIndex == -1) {
        return;
    }

    OptThemeUI * d = (OptThemeUI*) w;
    QString themeName = d->themeCB->currentText();

    delete theme;
    theme = new HTMLChatTheme(themeList.themePath(themeName));

    d->variantCB->clear();
    d->variantCB->addItems(theme->variants());
}


void OptionsTabThemes::onVariantLoaded(int variantIndex) {

    OptThemeUI * d = (OptThemeUI*) w;
    theme->setCurrentVariant(d->variantCB->currentText());
}


void OptionsTabThemes::applyOptions() {
    if (!w)
        return;

    OptThemeUI *d = (OptThemeUI *) w;

    PsiOptions::instance()->setOption("options.ui.themes.htmlviewinmuc", d->useHtmlViewInMucCK->isChecked());
    PsiOptions::instance()->setOption("options.ui.themes.htmlviewinchats", d->useHtmlViewInChatsCK->isChecked());
    
    if (theme) {
        PsiOptions::instance()->setOption("options.ui.themes.themename",
                                          d->themeCB->currentText()); 
        PsiOptions::instance()->setOption("options.ui.themes.variantname",
                                          theme->currentVariant());

    }
}


void OptionsTabThemes::restoreOptions() {


    if (!w) {
        return;
    }

    OptThemeUI * d = (OptThemeUI *) w;
    d->useHtmlViewInMucCK->setChecked(PsiOptions::instance()->getOption("options.ui.themes.htmlviewinmuc").toBool());
    d->useHtmlViewInChatsCK->setChecked(PsiOptions::instance()->getOption("options.ui.themes.htmlviewinchats").toBool());

    themeList.readThemes(ApplicationInfo::homeDir());

    d->themeCB->clear();
    d->themeCB->addItems(themeList.themeNames());

    d->themeCB->setCurrentIndex(d->themeCB->findText(PsiOptions::instance()->getOption("options.ui.themes.themename").toString()));
    d->variantCB->setCurrentIndex(d->variantCB->findText(PsiOptions::instance()->getOption("options.ui.themes.variantname").toString()));

}


void OptionsTabThemes::setData(PsiCon *, QWidget *p) {
    parentWidget = p;
}
