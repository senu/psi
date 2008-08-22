#ifndef OPT_ADVANCED_H
#define OPT_ADVANCED_H

#include "optionstab.h"

class QWidget;

/** 
 * It's 'Misc.' options tab. 
 * 
 * If you are looking for 'Advanced' options try opt_tree.h 
 */
class OptionsTabAdvanced : public OptionsTab
{
	Q_OBJECT
public:
	OptionsTabAdvanced(QObject *parent);
	~OptionsTabAdvanced();

	QWidget *widget();
	void applyOptions();
	void restoreOptions();

private:
	QWidget *w;
};

#endif
