#include <gtest/gtest.h>

#include <suuri_math.hpp>

namespace su = suuri;

TEST(PrimitiveIntSuuriMath, Sign)
{
	{
		int8_t a = 0;
		EXPECT_EQ(su::sgn(a), 0);

		a = 1;
		EXPECT_EQ(su::sgn(a), 1);

		a = -1;
		EXPECT_EQ(su::sgn(a), -1);

		a = 100;
		EXPECT_EQ(su::sgn(a), 1);

		a = -100;
		EXPECT_EQ(su::sgn(a), -1);
	}
	{
		int64_t a = 0;
		EXPECT_EQ(su::sgn(a), 0);

		a = 1;
		EXPECT_EQ(su::sgn(a), 1);

		a = -1;
		EXPECT_EQ(su::sgn(a), -1);

		a = 100;
		EXPECT_EQ(su::sgn(a), 1);

		a = -100;
		EXPECT_EQ(su::sgn(a), -1);

		a = std::numeric_limits<int64_t>::max();
		EXPECT_EQ(su::sgn(a), 1);

		a = std::numeric_limits<int64_t>::min();
		EXPECT_EQ(su::sgn(a), -1);
	}
}

TEST(PrimitiveIntSuuriMath, AbsoluteValue)
{
	{
		int8_t a = 0;
		EXPECT_EQ(su::abs(a), a);

		a = 1;
		EXPECT_EQ(su::abs(a), a);

		a = -1;
		EXPECT_EQ(su::abs(a), -a);

		a = 100;
		EXPECT_EQ(su::abs(a), a);

		a = -100;
		EXPECT_EQ(su::abs(a), -a);
	}
	{
		int64_t a = 0;
		EXPECT_EQ(su::abs(a), a);

		a = 1;
		EXPECT_EQ(su::abs(a), a);

		a = -1;
		EXPECT_EQ(su::abs(a), -a);

		a = 100;
		EXPECT_EQ(su::abs(a), a);

		a = -100;
		EXPECT_EQ(su::abs(a), -a);

		a = std::numeric_limits<int64_t>::max();
		EXPECT_EQ(su::abs(a), a);

		a = std::numeric_limits<int64_t>::min();
		EXPECT_EQ(su::abs(a), -a);
	}
}

TEST(PrimitiveIntSuuriMath, Pow)
{
	{
		int8_t a = 0;
		EXPECT_EQ(su::pow(a, 1), 0);
		EXPECT_EQ(su::pow(a, 2), 0);

		a = 1;
		EXPECT_EQ(su::pow(a, 0), 1);
		EXPECT_EQ(su::pow(a, 1), 1);
		EXPECT_EQ(su::pow(a, 2), 1);

		a = 2;
		EXPECT_EQ(su::pow(a, 0), 1);
		EXPECT_EQ(su::pow(a, 1), 2);
		EXPECT_EQ(su::pow(a, 2), 4);
	}
	{
		int64_t a = 0;
		EXPECT_EQ(su::pow(a, 1), 0);
		EXPECT_EQ(su::pow(a, 2), 0);

		a = 1;
		EXPECT_EQ(su::pow(a, 0), 1);
		EXPECT_EQ(su::pow(a, 1), 1);
		EXPECT_EQ(su::pow(a, 2), 1);

		a = 2;
		EXPECT_EQ(su::pow(a, 0), 1);
		EXPECT_EQ(su::pow(a, 1), 2);
		EXPECT_EQ(su::pow(a, 2), 4);

		a = 3;
		EXPECT_EQ(su::pow(a, 0), 1);
		EXPECT_EQ(su::pow(a, 1), 3);
		EXPECT_EQ(su::pow(a, 2), 9);
		EXPECT_EQ(su::pow(a, 3), 27);

		a = 5;
		EXPECT_EQ(su::pow(a, 0), 1);
		EXPECT_EQ(su::pow(a, 1), 5);
		EXPECT_EQ(su::pow(a, 2), 25);
		EXPECT_EQ(su::pow(a, 3), 125);
		EXPECT_EQ(su::pow(a, 27), 7450580596923828125);
	}
}
