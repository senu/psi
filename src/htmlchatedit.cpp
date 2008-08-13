#include "htmlchatedit.h"
#include "messageValidator.h"
#include "addurldlg.h"
#include "textutil.h"
#include "imagedownloaddialog.h"


HTMLChatEdit::HTMLChatEdit(QWidget* parent)
: ChatEdit(parent) {

    formatToolBar = new QToolBar(this);
    formatToolBar->setIconSize(QSize(16, 16));

    initActions();

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
    qDebug() << "bg" << format.background().color();
    format.setBackground(color);
    qDebug() << "bg2" << format.background().color();

    mergeFormat(format);
}


void HTMLChatEdit::insertImage() {

    ImageDownloadDialog * dlg = new ImageDownloadDialog(this);
    dlg->setWindowModality(Qt::WindowModal);

    connect(dlg, SIGNAL(finished(const QString&, const QImage&)),
            this, SLOT(insertImageDialogFinished(const QString&, const QImage&)));

    dlg->show();
}


void HTMLChatEdit::insertImageDialogFinished(const QString& url, const QImage& image) {

    if (image.isNull()) {
        return;
    }

    document()->addResource(QTextDocument::ImageResource, QUrl(url), image);

    QTextCursor cursor = textCursor();
    cursor.insertImage(url);

}


void HTMLChatEdit::insertAnchor() {

    AddUrlDlg *w = new AddUrlDlg(this);
    w->setWindowTitle(tr("Insert hyperlink"));

    if (w->exec() != QDialog::Accepted) {


        delete w;
        return;
    }

    QString href = TextUtil::escape(w->le_url->text());
    QString desc = TextUtil::escape(w->le_desc->text());

    delete w;

    textCursor().insertHtml(QString("<a href=\"%1\">%2</a> ").arg(href, desc));
}


void HTMLChatEdit::changeAlignButtons() {


    qDebug() << "bg test" << textCursor().charFormat().background().color()
        << textCursor().charFormat().background().color().isValid();


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

    if (format.background().color() == QTextCharFormat().background().color()) {
        pixmap.fill(Qt::white); //NOTE: it's Qt bug, I think. it's black by default, but displayed as white
    }
    else {


        pixmap.fill(format.background().color());
    }
    actionBackgroundColor->setIcon(pixmap);

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


    QString iconPath("/home/senu/dev/psi/gsoc/psi-fork/src/icons/"); //TODO + 42 iconServer
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
    QPixmap pixmap(14, 14); //TODO 43 fore and background color icon
    pixmap.fill(Qt::black);
    actionForegroundColor = new QAction(pixmap, tr("&Foreground color..."), this);

    pixmap.fill(Qt::white);
    actionBackgroundColor = new QAction(pixmap, tr("&Background color..."), this);


    //font size
    sizeCombo = new QComboBox(0);
    sizeCombo->setEditable(true);

    QFontDatabase fontDB;


    foreach(int size, fontDB.standardSizes()) {


        sizeCombo->addItem(QString::number(size));
    }

    sizeCombo->setCurrentIndex(sizeCombo->findText(QString::number(font().pointSize())));

    //font family
    fontCombo = new QFontComboBox(0);


    //add hyperling, add image
    actionInsertHyperlink = new QAction(QIcon(iconPath + "textjustify.png"), tr("Insert &hyperlink"), this);
    actionInsertImage = new QAction(QIcon(iconPath + "textjustify.png"), tr("Insert ima&ge"), this);

    //append to toolbar
    formatToolBar->addWidget(fontCombo);
    formatToolBar->addWidget(sizeCombo);

    formatToolBar->addSeparator();

    formatToolBar->addAction(actionTextBold);
    formatToolBar->addAction(actionTextItalic);
    formatToolBar->addAction(actionTextUnderline);

    formatToolBar->addSeparator();

    formatToolBar->addAction(actionAlignLeft);
    formatToolBar->addAction(actionAlignCenter);
    formatToolBar->addAction(actionAlignRight);
    formatToolBar->addAction(actionAlignJustify);

    formatToolBar->addSeparator();

    formatToolBar->addAction(actionForegroundColor);
    formatToolBar->addAction(actionBackgroundColor);

    formatToolBar->addSeparator();

    formatToolBar->addAction(actionInsertHyperlink);
    formatToolBar->addAction(actionInsertImage);


    //connect actions
    connect(fontCombo, SIGNAL(activated(const QString &)), this, SLOT(fontFamily(const QString &)));
    connect(sizeCombo, SIGNAL(activated(const QString &)), this, SLOT(fontSize(const QString &)));

    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));

    connect(alignActions, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

    connect(actionForegroundColor, SIGNAL(triggered()), this, SLOT(textForegroundColor()));
    connect(actionBackgroundColor, SIGNAL(triggered()), this, SLOT(textBackgroundColor()));

    connect(actionInsertHyperlink, SIGNAL(triggered()), this, SLOT(insertAnchor()));
    connect(actionInsertImage, SIGNAL(triggered()), this, SLOT(insertImage()));
}


HTMLChatEdit::~HTMLChatEdit() {


    delete formatToolBar;
    qDebug() << xhtmlMessage();
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

    QTextCharFormat defaultCharFormat;

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
    if (fragmentFormat.fontItalic()) {
        style += "; font-style:" + QLatin1String("italic");
    }

    if (fragmentFormat.hasProperty(QTextFormat::FontWeight)) {
        style += QLatin1String("; font-weight:");
        style += QString::number(fragmentFormat.fontWeight() * 8);
    }

    //font-family
    if (!fragmentFormat.fontFamily().isEmpty()) {
        if (fragmentFormat.fontFamily().contains('\'')) {
            style += "; font-family: \"" + fragmentFormat.fontFamily() + "\"";
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

    if (fragmentFormat.foreground() != defaultCharFormat.foreground()) {
        style += "; color:" + fragmentFormat.foreground().color().name();
    }

    if (fragmentFormat.background() != defaultCharFormat.background()) {
        style += "; background-color:" + fragmentFormat.background().color().name() + ";";
    }

    return style;
}


QString HTMLChatEdit::xhtmlMessage() {

    QString msg; //new message [ QTextDocument -> xhtml-im ];

    QTextBlock currentBlock = document()->begin();


    //each textBlock [== text, image, hyperlink] - we omit tables, lists, frames
    while (currentBlock.isValid()) {
        QTextBlockFormat curTBF = currentBlock.blockFormat();

        QString block = ""; //inner of block 

        //each framgent
        for (QTextBlock::iterator it = currentBlock.begin(); !(it.atEnd()); ++it) {
            QTextFragment currentFragment = it.fragment();

            if (currentFragment.isValid()) {
                QTextCharFormat curTCF = currentFragment.charFormat();

                if (curTCF.isImageFormat()) {
                    block += "<img src=\"" + TextUtil::escape(curTCF.toImageFormat().name()) + "\" alt=\"image\"/>";
                }
                else if (!curTCF.anchorHref().isEmpty()) {
                    block += "<a href=\"" + TextUtil::escape(curTCF.anchorHref()) + "\">" +
                        TextUtil::escape(currentFragment.text()) + "</a>";
                }
                else {
                    block += "<span style=\"" + createFragmentStyle(curTCF) + "\">"
                        + TextUtil::escape(currentFragment.text()) + "</span>";
                }

            }
        }

        if (document()->blockCount() == 1 && curTBF.alignment() == Qt::AlignLeft) { //we dont need extra new lines (<p>) for ordinary messages
            msg += block;
        }
        else {


            msg += "<p style=\"" + createBlockStyle(curTBF) + "\">" + block + "</p>";
        }

        currentBlock = currentBlock.next();
    }

    qDebug() << "created message" << msg;
    return "<body><span>" + msg + "</span></body>";
}


QString HTMLChatEdit::messageBody(bool xhtml) {
    if (xhtml) {
        return xhtmlMessage();
    }
    else {


        return toPlainText();
    }
}


QToolBar* HTMLChatEdit::toolBar() const {
    return formatToolBar;
}


