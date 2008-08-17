#ifndef HAVE_HTML_CHAT_PART
#define HAVE_HTML_CHAT_PART

#include <QString>
#include <QtDebug>
#include <QDateTime> 
#include <QColor> 


/** 
 * Part (string) of HTMLChat document (eg. newly created message/event).
 *
 * Main methods: replaceAndEscapeKeyword(key, value), toString().
 *
 *  Usage:
 *
 *   HTMLChatPart part = fileTransferEventTemplate.createFreshHTMLPart();
 *   part.replaceAndEscapeKeyword("%status%", statusStr);
 */
class HTMLChatPart {

public:

    HTMLChatPart();

    /** Creates HTMLChatPart with body = content*/
    HTMLChatPart(const QString _content);

    /** Replaces occurence of %keyword% with escaped value */
    void replaceAndEscapeKeyword(QString keyword, QString value);

    /* 
     * "Replaces" occurence of %message% with escaped value;
     *
     * \param value is stored (messageBody()) and is replaced in JavaScript code after 
     * CSS validation/transformermation.
     */
    void replaceMessageBody(QString value);

    /** Replaces time keyword %keyword{format}% with formatted time */
    void replaceTimeKeyword(QString keyword, QDateTime time);

    /** Replaces time keyword %senderColor% with color computed using userHash */
    void replaceSenderColorKeyword(const QColor& userColor);

    /** Creates 'short time' string (%shortTime%) */
    static QString createShortTime(const QDateTime& time);

    /** 
     * Converts part to string.
     */
    QString toString() const;

    /** Returns value of %message% */
    QString messageBody() const;

private:
    /** Part body */
    QString content;

    /** Message body (%message%) */
    QString _messageBody;

    /** Returns formated time, eg for %timeOpened{X}% */
    QString formatTime(QString format, const QDateTime& time);
    
    /** Escapes string (% escaping) */ 
    QString escapeString(QString string); //TODO!!!
    
};

#endif
