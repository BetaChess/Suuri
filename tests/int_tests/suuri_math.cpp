#include <gtest/gtest.h>

#include <big_int.hpp>
#include <suuri_math.hpp>

namespace su = suuri;

TEST(IntSuuriMath, Sign)
{
	// Test su::sign of small integers
	su::big_int_t a = 0;
	EXPECT_EQ(su::sgn(a), 0);
	EXPECT_EQ(a.sgn(), 0);

	a = 1;
	EXPECT_EQ(su::sgn(a), 1);
	EXPECT_EQ(a.sgn(), 1);

	a = -1;
	EXPECT_EQ(su::sgn(a), -1);
	EXPECT_EQ(a.sgn(), -1);

	// Test su::sign of large integers
	a = su::big_int_t{"15743214890321324123414000000000000000000000000000000000000000000000"};
	EXPECT_EQ(su::sgn(a), 1);
	EXPECT_EQ(a.sgn(), 1);

	a = su::big_int_t{"-15743214890321324123414000000000000000000000000000000000000000000000"};
	EXPECT_EQ(su::sgn(a), -1);
	EXPECT_EQ(a.sgn(), -1);
}

TEST(IntSuuriMath, AbsoluteValue)
{
	su::big_int_t a = 0;
	EXPECT_EQ(su::abs(a), a);
	EXPECT_EQ(a.abs(), a);

	a = 1;
	EXPECT_EQ(su::abs(a), a);
	EXPECT_EQ(a.abs(), a);

	a = -1;
	EXPECT_EQ(su::abs(a), -a);
	EXPECT_EQ(a.abs(), -a);

	a = su::big_int_t{"15743214890321324123414000000000000000000000000000000000000000000000"};
	EXPECT_EQ(su::abs(a), a);
	EXPECT_EQ(a.abs(), a);

	a = su::big_int_t{"-15743214890321324123414000000000000000000000000000000000000000000000"};
	EXPECT_EQ(su::abs(a), -a);
	EXPECT_EQ(a.abs(), -a);
}

TEST(IntSuuriMath, Pow)
{
	// Test su::pow of small integers
	su::big_int_t a = 0;
	EXPECT_EQ(su::pow(a, 1), 0);
	EXPECT_EQ(a.pow(1), 0);

	EXPECT_EQ(su::pow(a, 2), 0);
	EXPECT_EQ(a.pow(2), 0);

	a = 1;
	EXPECT_EQ(su::pow(a, 0), 1);
	EXPECT_EQ(a.pow(0), 1);

	EXPECT_EQ(su::pow(a, 1), 1);
	EXPECT_EQ(a.pow(1), 1);

	EXPECT_EQ(su::pow(a, 2), 1);
	EXPECT_EQ(a.pow(2), 1);

	a = 2;
	EXPECT_EQ(su::pow(a, 0), 1);
	EXPECT_EQ(a.pow(0), 1);

	EXPECT_EQ(su::pow(a, 1), 2);
	EXPECT_EQ(a.pow(1), 2);

	EXPECT_EQ(su::pow(a, 2), 4);
	EXPECT_EQ(a.pow(2), 4);

	a = 5;
	EXPECT_EQ(su::pow(a, 0), 1);
	EXPECT_EQ(a.pow(0), 1);

	EXPECT_EQ(su::pow(a, 1), 5);
	EXPECT_EQ(a.pow(1), 5);

	EXPECT_EQ(su::pow(a, 2), 25);
	EXPECT_EQ(a.pow(2), 25);

	// Test su::pow of large integers
	a = su::big_int_t{"123546"};
	EXPECT_EQ(su::pow(a, 0), 1);
	EXPECT_EQ(a.pow(0), 1);

	EXPECT_EQ(su::pow(a, 1), a);
	EXPECT_EQ(a.pow(1), a);

	EXPECT_EQ(su::pow(a, 2), a * a);
	EXPECT_EQ(a.pow(2), a * a);

	EXPECT_EQ(su::pow(a, 3), a * a * a);
	EXPECT_EQ(a.pow(3), a * a * a);

	EXPECT_EQ(su::pow(a, 20), su::big_int_t{"686394475970957575528162329744850259123595018357328157281789909574621132884063828987026930102646603776"});
	EXPECT_EQ(a.pow(20), su::big_int_t{"686394475970957575528162329744850259123595018357328157281789909574621132884063828987026930102646603776"});
}
