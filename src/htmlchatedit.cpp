#include "htmlchatedit.h"
#include "messageValidator.h"


HTMLChatEdit::HTMLChatEdit(QWidget* parent, QToolBar * _toolBar, const QString& _iconPath)
: QTextEdit(parent), iconPath(_iconPath) {

    toolBar = _toolBar;

    initActions();

    setText("Lorem ipsum costam costam i jeszcze cos tam costam.");

    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(changeAlignButtons()));
    connect(this, SIGNAL(currentCharFormatChanged(const QTextCharFormat&)),
            this, SLOT(changeTextButtons(const QTextCharFormat&)));

    show();
}


void HTMLChatEdit::textBold() {
    QTextCharFormat format;
    format.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);

    mergeFormat(format);

}


void HTMLChatEdit::textItalic() {
    QTextCharFormat format;
    format.setFontItalic(actionTextItalic->isChecked());

    mergeFormat(format);
}


void HTMLChatEdit::textUnderline() {
    QTextCharFormat format;
    format.setFontUnderline(actionTextUnderline->isChecked());

    mergeFormat(format);
}


void HTMLChatEdit::textAlign(QAction* alignAction) {
    setAlignment((Qt::Alignment)alignAction->property("align").toInt());
}


void HTMLChatEdit::fontFamily(const QString& fontName) {
    QTextCharFormat format;
    format.setFontFamily(fontName);

    mergeFormat(format);
}


void HTMLChatEdit::fontSize(const QString& size) {
    QTextCharFormat format;
    format.setFontPointSize(size.toFloat());

    mergeFormat(format);
}


void HTMLChatEdit::textForegroundColor() {
    QColor color = QColorDialog::getColor(textColor(), this);

    if (!color.isValid()) {
        return;
    }

    QTextCharFormat format;
    format.setForeground(color);

    mergeFormat(format);
}


void HTMLChatEdit::textBackgroundColor() {
    QColor color = QColorDialog::getColor(textColor(), this);

    if (!color.isValid()) {
        return;
    }

    QTextCharFormat format;
    format.setBackground(color);

    mergeFormat(format);
}


void HTMLChatEdit::insertImage() { //TODO

    QTextCursor cursor = textCursor();
    QImage img = QImage("/usr/share/icons/oxygen/128x128/apps/kmail.png");
    document()->addResource(QTextDocument::ImageResource, QUrl("myimage"), img);

    cursor.insertImage("myimage");
}


void HTMLChatEdit::insertAnchor() { //TODO
    QString href = "http://google.com";
    QString name = "visit psi";

    textCursor().insertHtml(QString("<a href=\"%1\">%2</a><strong style=\"dupa: placki; font-family: 'F\"ixed'; color: red;\">zzzz</strong>").arg(href).arg(name)); //TODO escape
}


void HTMLChatEdit::changeAlignButtons() {
    //    qDebug() << cursor(). format.background().color();

    Qt::Alignment aligment = alignment();


    foreach(QAction* action, alignActions->actions()) {
        if (action->property("align").toInt() & aligment) {
            action->setChecked(true);
            break;
        }
    }
}


void HTMLChatEdit::changeTextButtons(const QTextCharFormat& format) {

    qDebug() << format.background().color();
    QFont font = format.font();

    actionTextBold->setChecked(font.bold());
    actionTextItalic->setChecked(font.italic());
    actionTextUnderline->setChecked(font.underline());

    fontCombo->setCurrentIndex(fontCombo->findText(font.family()));
    sizeCombo->setCurrentIndex(sizeCombo->findText(QString::number(font.pointSize())));

    QPixmap pixmap(14, 14);

    pixmap.fill(format.foreground().color());
    actionForegroundColor->setIcon(pixmap);

    pixmap.fill(format.background().color());
    actionBackgroundColor->setIcon(pixmap); //TODO format.background().color() is wrong after style/font change

}


void HTMLChatEdit::mergeFormat(const QTextCharFormat& format) {
    QTextCursor cursor = textCursor();

    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }

    cursor.mergeCharFormat(format);
    mergeCurrentCharFormat(format);
}


void HTMLChatEdit::initActions() {

    //font style
    actionTextBold = new QAction(QIcon(iconPath + "textbold.png"), tr("&Bold"), this);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setCheckable(true);

    actionTextItalic = new QAction(QIcon(iconPath + "textitalic.png"), tr("&Italic"), this);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(QIcon(iconPath + "textunder.png"), tr("&Underline"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    actionTextUnderline->setCheckable(true);

    //align
    alignActions = new QActionGroup(this);

    actionAlignLeft = new QAction(QIcon(iconPath + "textleft.png"), tr("&Left"), alignActions);
    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setProperty("align", Qt::AlignLeft);
    actionAlignLeft->setCheckable(true);

    actionAlignCenter = new QAction(QIcon(iconPath + "textcenter.png"), tr("C&enter"), alignActions);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setProperty("align", Qt::AlignCenter);
    actionAlignCenter->setCheckable(true);

    actionAlignRight = new QAction(QIcon(iconPath + "textright.png"), tr("&Right"), alignActions);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setProperty("align", Qt::AlignRight);
    actionAlignRight->setCheckable(true);

    actionAlignJustify = new QAction(QIcon(iconPath + "textjustify.png"), tr("&Justify"), alignActions);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setProperty("align", Qt::AlignJustify);
    actionAlignJustify->setCheckable(true);

    //colors
    QPixmap pixmap(14, 14); //TODO fore and background color icon
    pixmap.fill(Qt::black);
    actionForegroundColor = new QAction(pixmap, tr("&Foreground color..."), this);

    pixmap.fill(Qt::white);
    actionBackgroundColor = new QAction(pixmap, tr("&Background color..."), this);


    //font size
    sizeCombo = new QComboBox(toolBar);
    sizeCombo->setEditable(true);

    QFontDatabase fontDB;


    foreach(int size, fontDB.standardSizes()) {
        sizeCombo->addItem(QString::number(size));
    }

    sizeCombo->setCurrentIndex(sizeCombo->findText(QString::number(font().pointSize()))); //TODO ?(fontPointSize())));

    //font family
    fontCombo = new QFontComboBox(toolBar);


    //append to toolbar
    toolBar->addWidget(fontCombo);
    toolBar->addWidget(sizeCombo);

    toolBar->addSeparator();

    toolBar->addAction(actionTextBold);
    toolBar->addAction(actionTextItalic);
    toolBar->addAction(actionTextUnderline);

    toolBar->addSeparator();

    toolBar->addAction(actionAlignLeft);
    toolBar->addAction(actionAlignCenter);
    toolBar->addAction(actionAlignRight);
    toolBar->addAction(actionAlignJustify);

    toolBar->addSeparator();

    toolBar->addAction(actionForegroundColor);
    toolBar->addAction(actionBackgroundColor);


    //connect actions
    connect(fontCombo, SIGNAL(activated(const QString &)), this, SLOT(fontFamily(const QString &)));
    connect(sizeCombo, SIGNAL(activated(const QString &)), this, SLOT(fontSize(const QString &)));

    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));

    connect(alignActions, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

    connect(actionForegroundColor, SIGNAL(triggered()), this, SLOT(textForegroundColor()));
    connect(actionBackgroundColor, SIGNAL(triggered()), this, SLOT(textBackgroundColor()));
}


HTMLChatEdit::~HTMLChatEdit() {
    qDebug() << message();
}


QString HTMLChatEdit::createBlockStyle(const QTextBlockFormat& blockFormat) {
    QString style = "text-align:";

    switch (blockFormat.alignment()) {
        case Qt::AlignLeft :
                    style += "left";
            break;
        case Qt::AlignRight :
                    style += "right";
            break;
        case Qt::AlignCenter :
                    style += "center";
            break;
        case Qt::AlignJustify :
                    style += "justify";
            break;
    }

    return style;
}


QString HTMLChatEdit::createFragmentStyle(const QTextCharFormat& fragmentFormat) {
    QString style = "text-decoration:";

    //text-decoration
    bool haveOneDec = false; // at least one decoration

    if (fragmentFormat.fontOverline()) {
        haveOneDec = true;
        style += " overline";
    }

    if (fragmentFormat.fontUnderline()) {
        haveOneDec = true;
        style += " underline";
    }

    if (fragmentFormat.fontStrikeOut()) {
        haveOneDec = true;
        style += " line-through";
    }

    if (!haveOneDec) {
        style += "none";
    }

    //font-style
    style += "; font-style:" + (fragmentFormat.fontItalic() ? QLatin1String("italic") : QLatin1String("normal"));

    if (fragmentFormat.hasProperty(QTextFormat::FontWeight)) {
        style += QLatin1String("; font-weight:");
        style += QString::number(fragmentFormat.fontWeight() * 8); //TODO
    }

    //font-family
    if (!fragmentFormat.fontFamily().isEmpty()) {
        if (fragmentFormat.fontFamily().contains('\'')) {
            style += "; font-family: \"" + fragmentFormat.fontFamily() + "\""; //todo escape!
        }
        else {
            style += "; font-family: '" + fragmentFormat.fontFamily() + "\'";
        }
    }

    //font-size
    if (fragmentFormat.hasProperty(QTextFormat::FontPointSize)) {
        style += "; font-size:" + QString::number(fragmentFormat.fontPointSize()) + "pt";
    }

    //colors
    style += "; color:" + fragmentFormat.foreground().color().name();
    //    style += "; background-color:" + fragmentFormat.background().color().name() + ";";

    return style;
}


QString HTMLChatEdit::message() { //TODO escape

    QString msg; //new message [ QTextDocument -> xhtml-im ];

    QTextBlock currentBlock = document()->begin();


    //each textBlock [== text, image, hyperlink] - we omit tables, lists, frames
    while (currentBlock.isValid()) {
        QTextBlockFormat curTBF = currentBlock.blockFormat();
        //        qDebug() << "TB" << currentBlock.text() << "[ " << curTBF.alignment() << " ]";

        QString block = ""; // inner of block 

        //each framgent
        for (QTextBlock::iterator it = currentBlock.begin(); !(it.atEnd()); ++it) {
            QTextFragment currentFragment = it.fragment();

            if (currentFragment.isValid()) {
                QTextCharFormat curTCF = currentFragment.charFormat();

                if (curTCF.isImageFormat()) {
                    block += "<img src=\"http://www.netbeans.org/images/v5/nb-logo2.gif\" ale=\"image\"/>";
                }
                else if (!curTCF.anchorHref().isEmpty()) {
                    block += "<a href=\"" + curTCF.anchorHref() + "\">" + currentFragment.text() + "</a>";

                }
                else {
                    block += "<span style=\"" + createFragmentStyle(curTCF) + "\">"
                            + currentFragment.text() + "</span>\n";
                }

            }
        }

        msg += "<p style=\"" + createBlockStyle(curTBF) + "\">" + block + "</p>\n";

        currentBlock = currentBlock.next();
    }


    return "<html><body><div>" + msg + "</div></body></html>";
}



