#ifndef _PLAINTEXTEVENTVIEW_H
#define	_PLAINTEXTEVENTVIEW_H

#include "psitextview.h"

/**
 * Old (PlaintText, non-Webkit) event viewer (used in EventDlg).
 * 
 * It offers better XHTML(-IM) rendering.
 * Most of its functionallity is implemented in PsiTextView.
 */
class PlainTextEventView : public PsiTextView {
    Q_OBJECT

public:
    PlainTextEventView(QWidget* parent);

    /** 
     * Displays xhtmlText.
     *
     * \param xhtmlText is XHTML string. It can have icon:// URLs
     */
    void displayText(const QString& xhtmlText);

signals:

    /** 
     * Emitted when user click on URL 
     * NOTE: this signal is never emitted, because PsiTextView handles URL by itself. //TODO!!!
     */
    void openURL(QString);
};

#endif

