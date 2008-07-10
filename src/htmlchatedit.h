#ifndef _HTMLCHATEDIT_H
#define	_HTMLCHATEDIT_H

#include <QTextEdit>
#include <QAction>
#include <QToolBar>
#include <QComboBox>
#include <QFontComboBox>
#include <QTextEdit>
#include <QTextCursor>
#include <QUrl>
#include <QImage>
#include <QtDebug>
#include <QActionGroup>
#include <QColor>
#include <QColorDialog>
#include <QFontDatabase>
#include <QTextBlock>


/** XHTML-IM message composer */
class HTMLChatEdit : public QTextEdit {

    Q_OBJECT
public:
    /** ToolBar is a QToolBar where actions/widgets are placed; iconPath is a path to icons/ dir */
    HTMLChatEdit(QWidget* parent, QToolBar* toolBar, const QString& iconPath);
    ~HTMLChatEdit();

    /** Returns XHTML-IM (validated) message */
    QString message();

    public
slots:
    void textBold();
    void textItalic();
    void textUnderline();

    void textAlign(QAction* alignAction);

    void fontFamily(const QString& fontName);
    void fontSize(const QString& size);
    void textForegroundColor();
    void textBackgroundColor();

    void insertImage();
    void insertAnchor();

    /** Show current text align */
    void changeAlignButtons();

    /** Show current text style */
    void changeTextButtons(const QTextCharFormat& format);


private:
    void mergeFormat(const QTextCharFormat &format);

    /*Creates and connects QActions */
    void initActions();

    //XHTML-IM message creator

    /** Creates \<p\> style attribute value */
    QString createBlockStyle(const QTextBlockFormat& blockFormat);
    
    /** Creates \<span\> (text fragment) style attribute value */
    QString createFragmentStyle(const QTextCharFormat& fragmentFormat);

    QToolBar * toolBar;
    QComboBox * sizeCombo;
    QFontComboBox * fontCombo;

    QAction *actionTextBold,
    *actionTextItalic,
    *actionTextUnderline,
    *actionForegroundColor,
    *actionBackgroundColor,
    *actionAlignLeft,
    *actionAlignCenter,
    *actionAlignRight,
    *actionAlignJustify;

    QActionGroup * alignActions;

    QString iconPath; //TODO we need icons we can use in Psi!
};

#endif

