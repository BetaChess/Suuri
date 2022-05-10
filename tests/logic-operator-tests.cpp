#include <gtest/gtest.h>

#include <big-int.h>

using namespace suuri;


TEST(LogicOperatorTests, Equals)
{
	{
		BigInt<uint64_t, 10> a = 2346;
		BigInt<uint64_t, 10> b = { {6, 4, 3, 2} };

		EXPECT_TRUE(a == b);
	}

	{
		BigInt<int64_t, 10> a = 2346;
		BigInt<int64_t, 10> b = { {6, 4, 3, 2} };

		EXPECT_TRUE(a == b);
	}

	{
		BigInt<uint64_t, 9223372036854775808ULL> a = 2346;
		BigInt<uint64_t, 9223372036854775808ULL> b = { {6, 4, 3, 2} };

		EXPECT_FALSE(a == b);
	}

	{
		BigInt<int64_t, 9223372036854775808LL> a = 2346;
		BigInt<int64_t, 9223372036854775808LL> b = { {2346} };

		EXPECT_TRUE(a == b);
	}

	{
		BigInt<uint64_t, 9223372036854775808ULL> a = 72589324759;
		BigInt<uint64_t, 9223372036854775808ULL> b = { {6, 4, 3, 2} };

		EXPECT_FALSE(a == b);
	}

	{
		BigInt<int64_t, 9223372036854775808LL> a = 72589324759;
		BigInt<int64_t, 9223372036854775808LL> b = { {72589324759} };

		EXPECT_TRUE(a == b);
	}

	{
		BigInt<uint64_t, 72589324758> a = 72589324759;
		BigInt<uint64_t, 72589324758> b = { {1, 1} };

		EXPECT_TRUE(a == b);
	}

	
}

TEST(LogicOperatorTests, LessThan) {

}

