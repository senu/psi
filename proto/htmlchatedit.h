#ifndef _HTMLCHATEDIT_H
#define	_HTMLCHATEDIT_H

#include <QTextEdit>


class HTMLChatEdit : public QTextEdit {

    Q_OBJECT
public:
    HTMLChatEdit(QWidget * parent);
	~HTMLChatEdit();

	void textUnderline();
    void textItalic();
	
    void textAlign();

	void fontFamily();
	void fontSize();
	void fontColor();
	void fontBackground();

	void insertImage();
	void insertAnchor();
	
	
    public
slots:
    void textBold();


};

#endif

