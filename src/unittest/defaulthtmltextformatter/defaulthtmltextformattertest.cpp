#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "../../nullhtmltextformatter.h"
#include "../../messagevalidator.h"
#include "defaulthtmltextformatter.h"


/** CppUnit unit test for MessageValidator */
class DefaultHTMLTextFormatterTest : public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE(DefaultHTMLTextFormatterTest);

    CPPUNIT_TEST(linkfy);
    CPPUNIT_TEST(meRemoving);
    CPPUNIT_TEST(legacyFormatting);
    CPPUNIT_TEST(nullString);
    CPPUNIT_TEST(escaping);
    //    CPPUNIT_TEST(plainTextIcons);
    //  CPPUNIT_TEST(htmlIcons);

    CPPUNIT_TEST_SUITE_END();

public:

protected:

    void linkfy();
    void meRemoving();
    void legacyFormatting();
    void nullString();

    /** Misc. escaping test */
    void escaping();

    void plainTextIcons(); //NOTE: cannot test it because TextUtil requires PsiIconset and PsiOptions
    void htmlIcons(); //NOTE: cannot test it because TextUtil requires PsiIconset and PsiOptions

    void qStringAssert(QString output, QString validOutput);

};

CPPUNIT_TEST_SUITE_REGISTRATION(DefaultHTMLTextFormatterTest);

// -----------------------------------------------------------------------------


void DefaultHTMLTextFormatterTest::linkfy() {
    DefaultHTMLTextFormatter formatter(true, true, true, true);

    QDomDocument doc;
    QDomElement parent = doc.createElement("p");

    QString output = formatter.format("abc fgh http://wp.pl senu@spam.pl", parent);
    qStringAssert(output, "abc fgh <a href=\"http://wp.pl\">http://wp.pl</a> <a href=\"mailto:senu@spam.pl\">senu@spam.pl</a>");

    output = formatter.format("abc fgh http://wp.pl ijk mailto:senu@spam.pl", parent);
    qStringAssert(output, "abc fgh <a href=\"http://wp.pl\">http://wp.pl</a> ijk mailto:<a href=\"mailto:senu@spam.pl\">senu@spam.pl</a>");

    output = formatter.format("http://wp.pl", parent);
    qStringAssert(output, "<a href=\"http://wp.pl\">http://wp.pl</a>");

    QDomElement parent2 = doc.createElement("a");

    output = formatter.format("http://wp.pl", parent2);
    qStringAssert(output, "http://wp.pl");
}


void DefaultHTMLTextFormatterTest::meRemoving() {

    DefaultHTMLTextFormatter formatter(true, true, true, true);
    formatter.setRemoveEmoteString(true);

    QDomDocument doc;
    QDomElement parent = doc.createElement("p");

    QString output = formatter.format("", parent);
    qStringAssert(output, "");

    output = formatter.format(" ", parent);
    qStringAssert(output, " ");

    output = formatter.format("\n", parent);
    qStringAssert(output, "\n");
    
    output = formatter.format("  \n \t  \n", parent);
    qStringAssert(output, "  \n \t  \n");

    QDomElement parent2 = doc.createElement("a");

    output = formatter.format("/me is testing textFormatter /me", parent2);
    qStringAssert(output, "is testing textFormatter /me");
    
    output = formatter.format("/me here /me should not be removed", parent2);
    qStringAssert(output, "/me here /me should not be removed");
}


void DefaultHTMLTextFormatterTest::legacyFormatting() {
    
    DefaultHTMLTextFormatter formatter(true, true, true, true);

    QDomDocument doc;
    QDomElement parent = doc.createElement("p");

    QString output = formatter.format("*bold* abcd *bold* sdf", parent);
    qStringAssert(output, "<b>*bold*</b> abcd <b>*bold*</b> sdf");
    
    output = formatter.format("_under_ abcd _under_ sdf", parent);
    qStringAssert(output, "<u>_under_</u> abcd <u>_under_</u> sdf");
    
    output = formatter.format("/italic/ abcd /italic/ sdf", parent);
    qStringAssert(output, "<i>/italic/</i> abcd <i>/italic/</i> sdf");
}


void DefaultHTMLTextFormatterTest::nullString() {
    
    DefaultHTMLTextFormatter formatter(true, true, true, true);

    QDomDocument doc;
    QDomElement parent = doc.createElement("p");

    QString output = formatter.format(QString(), parent);
    qStringAssert(output, QString());
}


void DefaultHTMLTextFormatterTest::escaping() {
    DefaultHTMLTextFormatter formatter(true, true, true, true);

    QDomDocument doc;
    QDomElement parent = doc.createElement("p");

    QString output = formatter.format("abcd \" \\ \\\" \\\\ efgh", parent);
    qStringAssert(output, "abcd \" \\ \\\" \\\\ efgh");
    
    output = formatter.format("abc < > \n abc", parent);
    qStringAssert(output, "abc < > \n abc");

    output = formatter.format("&quot; &amp; &lt; &gt; &nbsp;", parent);
    qStringAssert(output, "\" &amp; &lt; &gt; ");
    
}


void DefaultHTMLTextFormatterTest::qStringAssert(QString output, QString validOutput) {
    CPPUNIT_ASSERT_EQUAL(validOutput.toStdString(), output.toStdString());
}
