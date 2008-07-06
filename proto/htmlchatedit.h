#ifndef _HTMLCHATEDIT_H
#define	_HTMLCHATEDIT_H

#include <QTextEdit>
#include <QAction>
#include <QToolBar>
#include <QComboBox>
#include <QFontComboBox>


/** XHTML-IM message composer */
class HTMLChatEdit : public QTextEdit {

    Q_OBJECT
public:
    HTMLChatEdit(QWidget* parent, QToolBar* toolBar);
    ~HTMLChatEdit();

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

    void insertImage(QString url);
    void insertAnchor(QString url, QString name);

    void cursorPosChanged();

private:
    void mergeFormat(const QTextCharFormat &format);

    /*Creates and connects QActions */
    void initActions();

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

    QString iconPath; //TODO we need icons we can use in Psi!
};

#endif

