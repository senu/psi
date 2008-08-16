#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "../../nullhtmltextformatter.h"
#include "../../messagevalidator.h"

/** CppUnit unit test for MessageValidator */
class MessageValidatorTest : public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE(MessageValidatorTest);
	CPPUNIT_TEST(goodMessage);
	CPPUNIT_TEST(badTagWithChildrenMessage);
	CPPUNIT_TEST(manyBadTags);
	CPPUNIT_TEST(badAttributeMessage);
	CPPUNIT_TEST(cannotHaveTextAttr);
	CPPUNIT_TEST(emptyMessage);
	CPPUNIT_TEST(scriptInCDATAMessage);
	CPPUNIT_TEST_SUITE_END();

	public:

	protected:
	/** No changes in output message*/
	void goodMessage();
	void badTagWithChildrenMessage();
	void manyBadTags();
	void badAttributeMessage();
	void cannotHaveTextAttr();
	void emptyMessage();
	void scriptInCDATAMessage();

	void genericTest(QString inMessage, QString validMessage);

	MessageValidator val;
};

CPPUNIT_TEST_SUITE_REGISTRATION(MessageValidatorTest);

// -----------------------------------------------------------------------------
void MessageValidatorTest::goodMessage() {
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


void MessageValidatorTest::badTagWithChildrenMessage() {
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
void MessageValidatorTest::manyBadTags() {

	QString inMessage =
		"<?xml version='1.0' encoding='UTF-8'?>"
		"<div>senu tu byl"
		"<strong>i jest fajny</strong>"
		"joined te\\ \" &lt; &quot;&amp;xt?"
		"<script>"
		"<em>kursywa</em>"
		"<p>NOWAY</p>"
		"<br/>"
		"<b>wrong<span>ok</span></b>"
		"a teraz cos zupelnie z innej beczki"
		"</script>"
		"<p>"
		"<b>wrong<span>ok</span></b>"
		"</p>"
		"a teraz cos zupelnie z innej beczki 444"
		"<strong>x<!-- comment -->x</strong>"
		"</div>";

	QString validMessage =
		"<?xml version='1.0' encoding='UTF-8'?>"
		"<div>senu tu byl"
		"<strong>i jest fajny</strong>"
		"joined te\\ \" &lt; \"&amp;xt?"
		"<em>kursywa</em>"
		"<p>NOWAY</p>" 
		"<br/>"
		"wrong<span>ok</span>"
		"a teraz cos zupelnie z innej beczki"
		"<p>"
		"wrong<span>ok</span>"
		"</p>"
		"a teraz cos zupelnie z innej beczki 444"
		"<strong>x<!-- comment -->x</strong>"
		"</div>";

	genericTest(inMessage, validMessage);
}


void MessageValidatorTest::badAttributeMessage() {
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

void MessageValidatorTest::cannotHaveTextAttr() {
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

void MessageValidatorTest::emptyMessage() {
	QString inMessage =
		"<?xml version='1.0' encoding='UTF-8'?>";

	QString validMessage =
		"illformed message!!!";

	genericTest(inMessage, validMessage);
}


void MessageValidatorTest::scriptInCDATAMessage() {
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

void MessageValidatorTest::genericTest(QString inMessage, QString validMessage) {
	bool modified;
	HTMLTextFormatter* formatter = new NullHTMLTextFormatter();

	QString outMessage = val.validateMessage(inMessage, &modified, formatter).replace('\n', "");

	delete formatter;

	CPPUNIT_ASSERT_EQUAL(validMessage.toStdString(), outMessage.toStdString());

}
