#include <gtest/gtest.h>

#include <suurimath.h>

using namespace suuri;


TEST(LogicOperatorTestsInt, Equals)
{
	{
		BigInt<int64_t, 10> a = 2346;
		BigInt<int64_t, 10> b = { {6, 4, 3, 2} };

		EXPECT_EQ(a, b);
	}

	{
		BigInt_t a = 2346;
		BigInt_t b = { {6, 4, 3, 2} };

		EXPECT_NE(a, b);
	}

	{
		BigInt_t a = 2346;
		BigInt_t b = { {2346} };

		EXPECT_EQ(a, b);
	}

	{
		BigInt_t a = 72589324759;
		BigInt_t b = { {72589324759} };

		EXPECT_EQ(a, b);
	}

	{
		BigInt_t a = 72589324759;
		BigInt_t b = { {72589324759}, true };

		EXPECT_NE(a, b);
	}

	{
		BigInt<int64_t, 72589324758> a = 72589324759;
		BigInt<int64_t, 72589324758> b = { {1, 1} };

		EXPECT_EQ(a, b);
	}

	{
		BigInt<int8_t, 2> a = 8;
		BigInt<int8_t, 2> b = { {0, 0, 0, 1} };

		EXPECT_EQ(a, b);
	}

	{
		BigInt<int8_t, 2> a = 5;
		BigInt<int8_t, 2> b = { {1, 0, 1} };

		EXPECT_EQ(a, b);
	}

	{
		BigInt<int8_t, 2> a = 5;
		BigInt<int8_t, 2> b = { {0, 0, 1} };

		EXPECT_NE(a, b);
	}

	{
		BigInt<int8_t, 2> a = 5;
		BigInt<int8_t, 2> b = { {1, 0, 1}, true };

		EXPECT_NE(a, b);
	}

}

TEST(LogicOperatorTestsInt, LessThan)
{
	{
		BigInt_t a = 4324237;
		BigInt_t b = 4324238;

		EXPECT_LT(a, b);
	}

	{
		BigInt_t a = -432423423423;
		BigInt_t b = 0;

		EXPECT_LT(a, b);
	}

	{
		BigInt_t a = { {432423423423}, true };
		BigInt_t b = 0;

		EXPECT_LT(a, b);
	}

	{
		BigInt_t a = 0;
		BigInt_t b = 0;

		EXPECT_FALSE(a < b);
	}

	{
		BigInt_t a = 0;
		BigInt_t b = { {0}, true };

		EXPECT_FALSE(a < b);
	}

	{
		BigInt_t a = { {0}, true };
		BigInt_t b = 0;

		EXPECT_FALSE(a < b);
	}
}

TEST(LogicOperatorTestsInt, GreaterThan)
{
	{
		BigInt_t a = 4324238;
		BigInt_t b = 4324237;

		EXPECT_GT(a, b);
	}

	{
		BigInt_t a = 0;
		BigInt_t b = -432423423423;

		EXPECT_GT(a, b);
	}

	{
		BigInt_t a = 0;
		BigInt_t b = { {432423423423}, true };

		EXPECT_GT(a, b);
	}

	{
		BigInt_t a = 0;
		BigInt_t b = 0;

		EXPECT_FALSE(a > b);
	}

	{
		BigInt_t a = 0;
		BigInt_t b = { {0}, true };

		EXPECT_FALSE(a > b);
	}

	{
		BigInt_t a = { {0}, true };
		BigInt_t b = 0;

		EXPECT_FALSE(a > b);
	}
}

