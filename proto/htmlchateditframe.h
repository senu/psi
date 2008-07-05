#ifndef _HTMLCHATEDITFRAME_H
#define	_HTMLCHATEDITFRAME_H

#include "QWidget"
#include "htmlchatedit.h"

class HTMLChatEditFrame : public QWidget {

   Q_OBJECT

public:
	HTMLChatEditFrame(QWidget * parent);
	~HTMLChatEditFrame();

private:
	HTMLChatEdit * editor;

};

#endif

