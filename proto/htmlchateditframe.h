#ifndef _HTMLCHATEDITFRAME_H
#define	_HTMLCHATEDITFRAME_H

#include <QWidget>
#include <QToolBar>
#include "htmlchatedit.h"


/** XHTML-IM message composer + toolbar ? */
class HTMLChatEditFrame : public QWidget {

   Q_OBJECT

public:
	HTMLChatEditFrame(QWidget * parent);
	~HTMLChatEditFrame();

private:
	HTMLChatEdit * editor;
    QToolBar * toolBar;

};

#endif

