#ifndef _MESSAGEVALIDATOR_H
#define	_MESSAGEVALIDATOR_H

/** Performs XHTML-IM message validation (and cuts off bad elements/attributes) */
class MessageValidator {
	
public:	
	MessageValidator();
	~MessageValidator();

	/** Returns new (valid) XHTML message; modified is set to true if message was modified */
	QString validateMessage(QString message, bool* modified);
	
	

};



#endif	/* _MESSAGEVALIDATOR_H */

