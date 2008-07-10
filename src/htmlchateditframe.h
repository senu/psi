#ifndef _HTMLCHATEDITFRAME_H
#define	_HTMLCHATEDITFRAME_H

#include <QWidget>
#include <QToolBar>
#include "htmlchatedit.h"


/** XHTML-IM message composer + toolbar ? */
class HTMLChatEditFrame : public QWidget {

   Q_OBJECT

public:
    /** iconPath is a path to icons/ dir */
	HTMLChatEditFrame(QWidget * parent, const QString& iconPath);
	~HTMLChatEditFrame();

    /** Returns composed in editor XHTML-IM message */
    QString toHTML();


private:
	HTMLChatEdit * editor;
    QToolBar * toolBar;

};

#endif

