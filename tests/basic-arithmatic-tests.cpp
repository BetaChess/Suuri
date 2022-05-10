#include <gtest/gtest.h>

#include <big-int.h>

using namespace suuri;


TEST(BasicArithmaticTests, AdditionAssignment)
{
	{
		uint64_t aT = 32424;
		uint64_t bT = 12345;

		BigInt<uint64_t, 10ULL> a = aT;
		BigInt<uint64_t, 10ULL> b = bT;

		auto expected = BigInt<uint64_t, 10ULL>{ aT + bT };
		auto& result = a += b;
		
		EXPECT_EQ(expected, result);
	}

	{
		// 6146579286482282964442953260593222670238943757334182761889354366823054175489184
		BigInt_t a = { {0, 1, 4, 43, 666} }; 
		
		// 7167216610811069661488056849256262003550779692475604443555727843708043020908795432769630313287364245305219422956142388249553357248765
		BigInt_t b = { {1, 1, 4, 43, 4, 0, 0, 1} }; 

		BigInt_t expected = { {1, 2, 8, 86, 670, 0, 0, 1} };

		auto& result = a += b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt<uint32_t, 2> a =			{ {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<uint32_t, 2> b =			{ {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<uint32_t, 2> expected1 =	{ {1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1} };
		BigInt<uint32_t, 2> expected2 =	{ 2493753U };

		ASSERT_TRUE(expected1 == expected2);
		
		auto& result = a += b;
		
		EXPECT_TRUE(expected1 == result);
		EXPECT_TRUE(expected2 == result);
	}
}

