#ifndef _PSICHATEDIT_H
#define	_PSICHATEDIT_H

#include <QTextEdit>
#include "spellhighlighter.h"
#include "spellchecker.h"

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


class LineEdit : public ChatEdit {

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

