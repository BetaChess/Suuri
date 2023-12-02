#include <gtest/gtest.h>

#include <big_int.hpp>

namespace su = suuri;

TEST(IntSubtraction, IntegersPositivePositive)
{
	// Test subtraction of small integers (result should be less than 1073741824)
	{
		su::big_int_t a = 0;
		su::big_int_t b = 0;
		su::big_int_t c = a - b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = 0;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = 0;
		b = 1;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = 1;
		b = 1;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = 2;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = 2;
		b = 1;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = 536870911;
		b = 536870911;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = 11111;
		b = 1111111112;
		c = a - b;

		EXPECT_EQ(c, -1111100001);

		a = 1111111111;
		b = 11111;
		c = a - b;

		EXPECT_EQ(c, 1111100000);

		a = 1111111111;
		b = 1111111111;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = 1111111111;
		b = 1111111112;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = 1111111112;
		b = 1111111111;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = 1111111111;
		b = 1111111111111111111LL;
		c = a - b;

		EXPECT_EQ(c, -1111111110000000000LL);
	}
	
	// Test subtraction of large integers
	{
		su::big_int_t a = 1073741824;
		su::big_int_t b = 1073741824;
		su::big_int_t c = a - b;

		EXPECT_EQ(c, 0);

		a = 1073741824;
		b = 1073741825;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = 1073741825;
		b = 1073741824;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = 1073741824;
		b = 2147483647;
		c = a - b;

		EXPECT_EQ(c, -1073741823);

		a = 2147483647;
		b = 1073741824;
		c = a - b;

		EXPECT_EQ(c, 1073741823);

		a = 2147483647;
		b = 2147483647;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = 2147483647;
		b = 2147483648;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = 2147483648;
		b = 2147483647;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = 2147483647;
		b = 4294967295;
		c = a - b;

		EXPECT_EQ(c, -2147483648);

		a = 4294967295;
		b = 2147483647;
		c = a - b;

		EXPECT_EQ(c, 2147483648);

		a = 4294967295;
		b = 4294967295;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = 4294967295;
		b = 4294967296;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = 4294967296;
		b = 4294967295;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = 4294967295;
		b = 8589934591;
		c = a - b;

		EXPECT_EQ(c, -4294967296);
	}
	
	// Test of large integers (using string initializer)
	{
		su::big_int_t a("123456789012345678901234567890");
		su::big_int_t b("123456789012345678901234567890");
		su::big_int_t c = a - b;

		EXPECT_EQ(c, 0);

		a = su::big_int_t("123456789012345678901234567890");
		b = su::big_int_t("123456789012345678901234567891");
		c = a - b;

		EXPECT_EQ(c, -1);

		a = su::big_int_t("123456789012345678901234567891");
		b = su::big_int_t("123456789012345678901234567890");
		c = a - b;

		EXPECT_EQ(c, 1);

		a = su::big_int_t("123456789012345678901234567890");
		b = su::big_int_t("246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("-123456789012345678901234567890"));

		a = su::big_int_t("246913578024691357802469135780");
		b = su::big_int_t("123456789012345678901234567890");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("123456789012345678901234567890"));

		a = su::big_int_t("246913578024691357802469135780");
		b = su::big_int_t("246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, 0);

		a = su::big_int_t("246913578024691357802469135780");
		b = su::big_int_t("246913578024691357802469135781");
		c = a - b;

		EXPECT_EQ(c, -1);

		a = su::big_int_t("246913578024691357802469135781");
		b = su::big_int_t("246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, 1);

		a = su::big_int_t("246913578024691357802469135780");
		b = su::big_int_t("493827156049382715604938271560");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("-246913578024691357802469135780"));
	}
}

TEST(IntSubtraction, IntegersNegativeNegative)
{
	// Test subtraction of small integers (result should be less than 1073741824)
	{
		su::big_int_t a = -1;
		su::big_int_t b = -1;
		su::big_int_t c = a - b;

		EXPECT_EQ(c, 0);

		a = -1;
		b = -2;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = -2;
		b = -1;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = -536870911;
		b = -536870911;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = -11111;
		b = -1111111112;
		c = a - b;

		EXPECT_EQ(c, 1111100001);

		a = -1111111111;
		b = -11111;
		c = a - b;

		EXPECT_EQ(c, -1111122222);

		a = -1111111111;
		b = -1111111111;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = -1111111111;
		b = -1111111112;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = -1111111112;
		b = -1111111111;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = -1111111111;
		b = -1111111111111111111;
		c = a - b;

		EXPECT_EQ(c, 1111111110000000000);
	}
	
	// Test subtraction of large integers
	{
		su::big_int_t a = -1073741824;
		su::big_int_t b = -1073741824;
		su::big_int_t c = a - b;

		EXPECT_EQ(c, 0);

		a = -1073741824;
		b = -1073741825;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = -1073741825;
		b = -1073741824;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = -1073741824;
		b = -2147483647;
		c = a - b;

		EXPECT_EQ(c, 1073741823);

		a = -2147483647;
		b = -1073741824;
		c = a - b;

		EXPECT_EQ(c, -1073741823);

		a = -2147483647;
		b = -2147483647;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = -2147483647;
		b = -2147483648;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = -2147483648;
		b = -2147483647;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = -2147483647;
		b = -4294967295;
		c = a - b;

		EXPECT_EQ(c, 2147483648);

		a = -4294967295;
		b = -2147483647;
		c = a - b;

		EXPECT_EQ(c, -2147483648);

		a = -4294967295;
		b = -4294967295;
		c = a - b;

		EXPECT_EQ(c, 0);

		a = -4294967295;
		b = -4294967296;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = -4294967296;
		b = -4294967295;
		c = a - b;

		EXPECT_EQ(c, -1);

		a = -4294967295;
		b = -8589934591;
		c = a - b;

		EXPECT_EQ(c, 4294967296);
	}
	
	// Test of large integers (using string initializer)
	{
		su::big_int_t a("-123456789012345678901234567890");
		su::big_int_t b("-123456789012345678901234567890");
		su::big_int_t c = a - b;

		EXPECT_EQ(c, 0);

		a = su::big_int_t("-123456789012345678901234567890");
		b = su::big_int_t("-123456789012345678901234567891");
		c = a - b;

		EXPECT_EQ(c, 1);

		a = su::big_int_t("-123456789012345678901234567891");
		b = su::big_int_t("-123456789012345678901234567890");
		c = a - b;

		EXPECT_EQ(c, -1);

		a = su::big_int_t("-123456789012345678901234567890");
		b = su::big_int_t("-246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("123456789012345678901234567890"));

		a = su::big_int_t("-246913578024691357802469135780");
		b = su::big_int_t("-123456789012345678901234567890");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("-123456789012345678901234567890"));

		a = su::big_int_t("-246913578024691357802469135780");
		b = su::big_int_t("-246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, 0);

		a = su::big_int_t("-246913578024691357802469135780");
		b = su::big_int_t("-246913578024691357802469135781");
		c = a - b;

		EXPECT_EQ(c, 1);

		a = su::big_int_t("-246913578024691357802469135781");
		b = su::big_int_t("-246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, -1);
	}
}

TEST(IntSubtraction, IntegersPositiveNegative)
{
	// Test subtraction of small integers
	{
		su::big_int_t a = 0;
		su::big_int_t b = 0;
		su::big_int_t c = a - b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = 0;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = 0;
		b = -1;
		c = a - b;

		EXPECT_EQ(c, 1);

		a = 1;
		b = -1;
		c = a - b;

		EXPECT_EQ(c, 2);

		a = 2;
		b = -1;
		c = a - b;

		EXPECT_EQ(c, 3);

		a = 536870911;
		b = -536870911;
		c = a - b;

		EXPECT_EQ(c, 1073741822);

		a = 11111;
		b = -1111111112;
		c = a - b;

		EXPECT_EQ(c, 1111122223);

		a = 1111111111;
		b = -11111;
		c = a - b;

		EXPECT_EQ(c, 1111122222);

		a = 1111111111;
		b = -1111111111;
		c = a - b;

		EXPECT_EQ(c, 2222222222);

		a = 1111111111;
		b = -1111111112;
		c = a - b;

		EXPECT_EQ(c, 2222222223);

		a = 1111111112;
		b = -1111111111;
		c = a - b;

		EXPECT_EQ(c, 2222222223);

		a = 1111111111;
		b = -1111111111111111111LL;
		c = a - b;

		EXPECT_EQ(c, 1111111112222222222LL);
	}
	
	// Test subtraction of large integers
	{
		su::big_int_t a = 1073741824;
		su::big_int_t b = -1073741824;
		su::big_int_t c = a - b;

		EXPECT_EQ(c, 2147483648);

		a = 1073741824;
		b = -1073741825;
		c = a - b;

		EXPECT_EQ(c, 2147483649);

		a = 1073741825;
		b = -1073741824;
		c = a - b;

		EXPECT_EQ(c, 2147483649);

		a = 1073741824;
		b = -2147483647;
		c = a - b;

		EXPECT_EQ(c, 3221225471);

		a = 2147483647;
		b = -1073741824;
		c = a - b;

		EXPECT_EQ(c, 3221225471);

		a = 2147483647;
		b = -2147483647;
		c = a - b;

		EXPECT_EQ(c, 4294967294);

		a = 2147483647;
		b = -2147483648;
		c = a - b;

		EXPECT_EQ(c, 4294967295);

		a = 2147483648;
		b = -2147483647;
		c = a - b;

		EXPECT_EQ(c, 4294967295);

		a = 2147483647;
		b = -4294967295;
		c = a - b;

		EXPECT_EQ(c, 6442450942);

		a = 4294967295;
		b = -2147483647;
		c = a - b;

		EXPECT_EQ(c, 6442450942);

		a = 4294967295;
		b = -4294967295;
		c = a - b;

		EXPECT_EQ(c, 8589934590);

		a = 4294967295;
		b = -4294967296;
		c = a - b;

		EXPECT_EQ(c, 8589934591);

		a = 4294967296;
		b = -4294967295;
		c = a - b;

		EXPECT_EQ(c, 8589934591);

		a = 4294967295;
		b = -8589934591;
		c = a - b;

		EXPECT_EQ(c, 12884901886);
	}
	
	// Test of large integers (using string initializer)
	{
		su::big_int_t a("123456789012345678901234567890");
		su::big_int_t b("-123456789012345678901234567890");
		su::big_int_t c = a - b;

		EXPECT_EQ(c, su::big_int_t("246913578024691357802469135780"));

		a = su::big_int_t("123456789012345678901234567890");
		b = su::big_int_t("-123456789012345678901234567891");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("246913578024691357802469135781"));

		a = su::big_int_t("123456789012345678901234567891");
		b = su::big_int_t("-123456789012345678901234567890");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("246913578024691357802469135781"));

		a = su::big_int_t("123456789012345678901234567890");
		b = su::big_int_t("-246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("370370367037036735703703703670"));

		a = su::big_int_t("246913578024691357802469135780");
		b = su::big_int_t("-123456789012345678901234567890");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("370370367037036735703703703670"));

		a = su::big_int_t("246913578024691357802469135780");
		b = su::big_int_t("-246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("493827156049382715604938271560"));

		a = su::big_int_t("246913578024691357802469135780");
		b = su::big_int_t("-246913578024691357802469135781");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("493827156049382715604938271561"));

		a = su::big_int_t("246913578024691357802469135781");
		b = su::big_int_t("-246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("493827156049382715604938271561"));

		a = su::big_int_t("246913578024691357802469135780");
		b = su::big_int_t("-493827156049382715604938271560");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("740740734074073471407407347340"));

		a = su::big_int_t("493827156049382715604938271560");
		b = su::big_int_t("-246913578024691357802469135780");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("740740734074073471407407347340"));

		a = su::big_int_t("493827156049382715604938271560");
		b = su::big_int_t("-493827156049382715604938271560");
		c = a - b;

		EXPECT_EQ(c, su::big_int_t("987654312098765431209876543120"));
	}
}
