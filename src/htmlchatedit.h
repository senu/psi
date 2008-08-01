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
#include "msgmle.h"


/** XHTML-IM message composer */
class HTMLChatEdit : public ChatEdit {

    Q_OBJECT
public:
    /** 
     * Constructor. 
     *
     * \param toolBar is a QToolBar where edit actions/widgets will be placed 
     */
    HTMLChatEdit(QWidget* parent);
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

    void insertImage();
    
    /** Pop-ups 'Add Hyperlink' dialog and inserts <a> element*/
    void insertAnchor();

    /** Show current text align */
    void changeAlignButtons();

    /** Show current text style */
    void changeTextButtons(const QTextCharFormat& format);
    
    //reimplemented
    QString messageBody(bool xhtml);
    QToolBar* toolBar() const;
    

protected:
    void mergeFormat(const QTextCharFormat &format);

    /*Creates and connects QActions */
    void initActions();

    //XHTML-IM message creator

    /** Creates \<p\> style attribute value */
    QString createBlockStyle(const QTextBlockFormat& blockFormat);
    
    /** Creates \<span\> (text fragment) style attribute value */
    QString createFragmentStyle(const QTextCharFormat& fragmentFormat);
    
    /** Returns XHTML-IM (validated) message wrapped with \<body\>\<\/body\>*/
    QString xhtmlMessage();

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
    *actionAlignJustify,
    *actionInsertHyperlink;

    QActionGroup * alignActions;

    QString iconPath; //TODO we need icons we can use in Psi!
    
    /** Formating toolbar */
    QToolBar* formatToolBar;

};

class LineEdit : public HTMLChatEdit { //TODO

    Q_OBJECT
public:
    LineEdit(QWidget* parent);
    ~LineEdit();

    // reimplemented
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    // reimplemented
    void resizeEvent(QResizeEvent*);

    private
slots:
    void recalculateSize();
    void updateScrollBar();
};


#endif

