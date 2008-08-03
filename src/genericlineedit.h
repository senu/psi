#ifndef _GENERICLINEEDIT_H
#define	_GENERICLINEEDIT_H

#include <QTimer>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include "psichatedit.h"
#include "htmlchatedit.h"


/** 
 * Auto-resizing ChatEdit
 * T have to inherit from ChatEdit 
 */
template <typename TEdit>
class GenericLineEdit : public TEdit {

public:


    GenericLineEdit(QWidget* parent)
    : TEdit(parent) {
        TEdit::setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere); // no need for horizontal scrollbar with this
        TEdit::setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TEdit::setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        TEdit::setMinimumHeight(0);

    }


    ~GenericLineEdit() {
    };


    // reimplemented


    QSize minimumSizeHint() const {
        QSize sh = TEdit::minimumSizeHint();
        sh.setHeight(TEdit::fontMetrics().height() + 1);
        sh += QSize(0, QFrame::lineWidth() * 2);
        return sh;
    }


    QSize sizeHint() const {
        QSize sh = TEdit::sizeHint();
        sh.setHeight(int(TEdit::document()->documentLayout()->documentSize().height()));
        sh += QSize(0, QFrame::lineWidth() * 2);
        ((TEdit*)this)->setMaximumHeight(sh.height());
        return sh;
    }

protected:


    void resizeEvent(QResizeEvent* e) {
        qDebug() << "gle:resizeEvent";
        TEdit::resizeEvent(e);
        QTimer::singleShot(0, this, SLOT(callUpdateScrollBar()));
    }


    void recalculateSize() {
        qDebug() << "gle:crs";
        TEdit::updateGeometry();
        QTimer::singleShot(0, this, SLOT(callUpdateScrollBar()));
    }


    void updateScrollBar() {
        qDebug() << "gle:usb";
        TEdit::setVerticalScrollBarPolicy(TEdit::sizeHint().height() > TEdit::height() ? Qt::ScrollBarAlwaysOn : Qt::ScrollBarAlwaysOff);
        TEdit::ensureCursorVisible();
    }

    /** It should call updateScrollbar, but it must be SLOT and Q_OBJECT doesnt work with templates */
    virtual void callUpdateScrollBar() = 0;

    /** Like callUpdateScrollBar */
    virtual void callRecalculateSize() = 0;

};

#endif
