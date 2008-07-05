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
            "<p>NOWAY</p>" 
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

void TestMessageValidator::cannotHaveTextAttr() {
    QString inMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
			"<div><hr/>"
            "<div>senu tu byl<br>i cannot be here!</br>"
            "<strong>STRONG</strong></div></div>";

    QString validMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
			"<div>"
            "<div>senu tu byl<br/>"
            "<strong>STRONG</strong></div></div>";

    genericTest(inMessage, validMessage);
	
}

void TestMessageValidator::emptyMessage() {
    QString inMessage =
            "<?xml version='1.0' encoding='UTF-8'?>";

    QString validMessage =
            "illformed message!!!";
			
    genericTest(inMessage, validMessage);
}


void TestMessageValidator::scriptInCDATAMessage() {
    QString inMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
			"<div>"
			"<![CDATA["
			"<script>xxx</script>]]>"
			"</div>";

    QString validMessage =
            "<?xml version='1.0' encoding='UTF-8'?>"
			"<div>"
			"<![CDATA["
			"<script>xxx</script>]]>"
			"</div>";
			
    genericTest(inMessage, validMessage);
	
}

void TestMessageValidator::genericTest(QString inMessage, QString validMessage) {
    bool modified;
    QString outMessage = val.validateMessage(inMessage, &modified).replace('\n', "");

    CPPUNIT_ASSERT_EQUAL(validMessage.toStdString(), outMessage.toStdString());

}


void TestMessageValidator::setUp() {

}