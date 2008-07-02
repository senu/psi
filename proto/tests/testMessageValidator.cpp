#include "testMessageValidator.h"
#include <QtDebug>


void TestMessageValidator::goodMessage() {
    QString inMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
            "<div>senu tu byl"
            "<strong>i jest fajny</strong>"
            "joined text?"
            "a teraz cos zupelnie z innej beczki 444"
            "<strong>x&nbsp;x</strong>"
            "</div>";

    QString validMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
            "<div>senu tu byl"
            "<strong>i jest fajny</strong>"
            "joined text?"
            "a teraz cos zupelnie z innej beczki 444"
            "<strong>x&nbsp;x</strong>"
            "</div>";

    genericTest(inMessage, validMessage);
}


void TestMessageValidator::badTagWithChildrenMessage() {
    QString inMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
            "<div>senu tu byl"
            "<strong>i jest fajny</strong>"
            "joined text?"
            "<script>"
            "<em>kursywa</em>"
            "<p>NOWAY</p>"
            "<br/>"
            "a teraz cos zupelnie z innej beczki"
            "</script>"

            "a teraz cos zupelnie z innej beczki 444"
            "<strong>x<!-- comment -->x</strong>"
            "</div>";

    QString validMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
            "<div>senu tu byl"
            "<strong>i jest fajny</strong>"
            "joined text?"
            "<em>kursywa</em>"
            " <p>NOWAY</p> " //TODO dont know why webkit prints here spaces
            "<br/>"
            "a teraz cos zupelnie z innej beczki"
            "a teraz cos zupelnie z innej beczki 444"
            "<strong>x<!-- comment -->x</strong>"
            "</div>";

    genericTest(inMessage, validMessage);

}


void TestMessageValidator::badAttributeMessage() {
    QString inMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
            "<div onclick=\"javascript:alert('oh no!')\" onload=\"javascript:alert('oh no!')\" >senu tu byl"
            "<strong onload=\"javascript:alert('oh no!')\">STRONG</strong></div>";

    QString validMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
            "<div>senu tu byl"
            "<strong>STRONG</strong></div>";

    genericTest(inMessage, validMessage);

}


void TestMessageValidator::badCSSMessage() {
    QString inMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
            "<div>"
            "<strong style=\"color: red; margin-left: 3px\">STRONG</strong>"
            "<strong style=\"color: red;\">STRONG</strong>"
            "<strong style=\"color: red\">STRONG</strong>"
            "<strong style=\"color:red\">STRONG</strong>"
            "<strong style=\"color:red;\">STRONG</strong>"
            "<strong style=\"color:red ;\">STRONG</strong>"
            "<strong style=\"color:\tred ;\">STRONG</strong>"
            "<strong style=\"color:   red ;\">STRONG</strong>"
            "<strong style=\"color:   red\">STRONG</strong>"
            "<strong style=\"color:   red    ;   margin-left:3px\">STRONG</strong>"
            
			"<strong style=\"color: red; postition:absolute\">STRONG</strong>"
            "<strong style=\"color: red\">STRONG</strong>"
			"</div>";

    QString validMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
            "<div>senu tu byl"
            "<strong>STRONG</strong></div>";

    genericTest(inMessage, validMessage);
}


void TestMessageValidator::badCSS2Message() {

}


void TestMessageValidator::badCSSURLMessage() {

}


void TestMessageValidator::genericTest(QString inMessage, QString validMessage) {
    bool modified;
    QString outMessage = val.validateMessage(inMessage, &modified).replace('\n', "");

    CPPUNIT_ASSERT_EQUAL(validMessage.toStdString(), outMessage.toStdString());

}


void TestMessageValidator::setUp() {

}