#ifndef _PSICHATEDIT_H
#define	_PSICHATEDIT_H

#include <QTextEdit>
#include <QToolBar>
#include "spellhighlighter.h"
#include "spellchecker.h"


/**
 * Message editor. 
 * 
 * Base of all message editing classes. It cannot compose XHTML-IM messages.
 */
class ChatEdit : public QTextEdit {

    Q_OBJECT

public:
    ChatEdit(QWidget* parent);
    ~ChatEdit();

    void setDialog(QWidget* dialog);

    // reimplemented
    QSize sizeHint() const;

    static bool checkSpellingGloballyEnabled();
    void setCheckSpelling(bool);

    /**
     * Returns message created with ChatEdit.
     *
     * if \param xhtml is true and ChatEdit can create XHTML-IM message it will return 
     * rich version of it. 
     *
     * if \param is true but ChatEdit cannot create XHTML-IM messages it will return null()
     * QString
     *
     * XHTML-IM message is wrapped with \<body\>\<\/body\>
     */
    virtual QString messageBody(bool xhtml); //TODO def. p

    /** 
     * Returns toolBar associated with this ChatEdit. 
     *
     * Default implementation returns NULL which means ChatEdit doesn't have a toolBar
     */
    virtual QToolBar* toolBar() const;


    protected
slots:
    void applySuggestion();
    void addToDictionary();
    void optionsChanged();

protected:
    // override the tab/esc behavior
    bool focusNextPrevChild(bool next);
    void keyPressEvent(QKeyEvent *);
    bool event(QEvent * event);
    void contextMenuEvent(QContextMenuEvent *e);

private:
    QWidget *dialog_;
    bool check_spelling_;
    SpellHighlighter* spellhighlighter_;
    QPoint last_click_;
    int previous_position_;
};

#endif	

