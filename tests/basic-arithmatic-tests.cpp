#include <gtest/gtest.h>

#include <suurimath.h>

#include <cmath>
#include <random>

using namespace suuri;


TEST(BasicArithmaticTests, AdditionAssignment)
{
	{
		int64_t aT = 32424;
		int64_t bT = 12345;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = BigInt<int64_t, 10ULL>{ aT + bT };
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
		BigInt<int32_t, 2> a = { {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int32_t, 2> b = { {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<int32_t, 2> expected1 = { {1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1} };
		BigInt<int32_t, 2> expected2 = { 2493753U };

		ASSERT_TRUE(expected1 == expected2);

		auto& result = a += b;

		EXPECT_TRUE(expected1 == result);
		EXPECT_TRUE(expected2 == result);
	}

	{
		BigInt<int8_t, 2> a =			{ {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int8_t, 2> b =			{ {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<int8_t, 2> expected1 =	{ {1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1} };
		BigInt<int8_t, 2> expected2 =	{ 2493753 };

		ASSERT_TRUE(expected1 == expected2);

		auto& result = a += b;

		EXPECT_TRUE(expected1 == result);
		EXPECT_TRUE(expected2 == result);
	}

	{
		BigInt_t a = 3217897;
		BigInt_t b = -3217897;

		BigInt_t expected = 0;
		auto& result = a += b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt_t a = 3217897;
		BigInt_t b = -3217899;

		BigInt_t expected = -2;
		auto& result = a += b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt_t a = BigInt_t::base() - 1;
		BigInt_t b = 2;

		BigInt_t expected = { {1, 1} };
		auto& result = a += b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt_t a = BigInt_t::base();
		BigInt_t b = -1;

		BigInt_t expected = BigInt_t::base() - 1;
		auto& result = a += b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt_t a = { {1, 1, 1} };
		BigInt_t b = { {1, 1, 1, 1, 1, 1}, true };

		BigInt_t expected = { {0, 0, 0, 1, 1, 1}, true };
		auto& result = a += b;

		EXPECT_EQ(expected, result);
	}

	{
		BigInt<int8_t, 2> a = { {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int8_t, 2> b = { {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1}, true };

		BigInt<int8_t, 2> expected1 = { {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, true };
		BigInt<int8_t, 2> expected2 = -2096637;

		ASSERT_EQ(expected1, expected2);

		auto& result = a += b;

		EXPECT_EQ(expected1, result);
		EXPECT_EQ(expected2, result);
	}

	{
		// Create randomizer
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int16_t> dis(std::numeric_limits<int16_t>::min() / 2, std::numeric_limits<int16_t>::max() / 2);

		/// RANDOM TEST
		for (size_t i = 0; i < 10000; i++)
		{
			auto aV = dis(gen);
			auto bV = dis(gen);

			BigInt<int16_t, 10> a = aV;
			BigInt<int16_t, 10> b = bV;

			auto expectedVal = aV + bV;
			BigInt<int16_t, 10> expected = expectedVal;
			auto& result = a += b;

			bool test = expected == result;

			ASSERT_EQ(expected, result) << "Values were: " << aV << " and " << bV;
		}
	}
}

TEST(BasicArithmaticTests, Addition)
{
	{
		int64_t aT = 32424;
		int64_t bT = 12345;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = BigInt<int64_t, 10ULL>{ aT + bT };
		auto result = a + b;

		EXPECT_EQ(expected, result);
	}

	{
		// 6146579286482282964442953260593222670238943757334182761889354366823054175489184
		BigInt_t a = { {0, 1, 4, 43, 666} };

		// 7167216610811069661488056849256262003550779692475604443555727843708043020908795432769630313287364245305219422956142388249553357248765
		BigInt_t b = { {1, 1, 4, 43, 4, 0, 0, 1} };

		BigInt_t expected = { {1, 2, 8, 86, 670, 0, 0, 1} };

		auto result = a + b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt<int32_t, 2> a = { {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int32_t, 2> b = { {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<int32_t, 2> expected1 = { {1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1} };
		BigInt<int32_t, 2> expected2 = { 2493753U };

		ASSERT_TRUE(expected1 == expected2);

		auto result = a + b;

		EXPECT_TRUE(expected1 == result);
		EXPECT_TRUE(expected2 == result);
	}

	{
		BigInt<int8_t, 2> a = { {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int8_t, 2> b = { {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<int8_t, 2> expected1 = { {1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1} };
		BigInt<int8_t, 2> expected2 = { 2493753 };

		ASSERT_TRUE(expected1 == expected2);

		auto result = a + b;

		EXPECT_TRUE(expected1 == result);
		EXPECT_TRUE(expected2 == result);
	}

	{
		BigInt_t a = 3217897;
		BigInt_t b = -3217897;

		BigInt_t expected = 0;
		auto result = a + b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt_t a = 3217897;
		BigInt_t b = -3217899;

		BigInt_t expected = -2;
		auto result = a + b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt_t a = BigInt_t::base() - 1;
		BigInt_t b = 2;

		BigInt_t expected = { {1, 1} };
		auto result = a + b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt_t a = BigInt_t::base();
		BigInt_t b = -1;

		BigInt_t expected = BigInt_t::base() - 1;
		auto result = a + b;

		EXPECT_TRUE(expected == result);
	}

	{
		BigInt<int8_t, 2> a = { {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int8_t, 2> b = { {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1}, true };

		BigInt<int8_t, 2> expected1 = { {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, true };
		BigInt<int8_t, 2> expected2 = -2096637;

		ASSERT_EQ(expected1, expected2);

		auto result = a + b;

		EXPECT_EQ(expected1, result);
		EXPECT_EQ(expected2, result);
	}

	{
		// Create randomizer
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int16_t> dis(std::numeric_limits<int16_t>::min() / 2, std::numeric_limits<int16_t>::max() / 2);

		/// RANDOM TEST
		for (size_t i = 0; i < 10000; i++)
		{
			auto aV = dis(gen);
			auto bV = dis(gen);

			BigInt<int16_t, 10> a = aV;
			BigInt<int16_t, 10> b = bV;

			auto expectedVal = aV + bV;
			BigInt<int16_t, 10> expected = expectedVal;
			auto result = a + b;

			bool test = expected == result;

			ASSERT_EQ(expected, result) << "Values were: " << aV << " and " << bV;
		}
	}
}

TEST(BasicArithmaticTests, SubtractionAssignment)
{
	{
		int64_t aT = 32424;
		int64_t bT = 12345;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = aT - bT ;
		auto& result = a -= b;

		EXPECT_EQ(expected, result);
	}

	{
		int64_t aT = -32424;
		int64_t bT = 12345;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = aT - bT;
		auto& result = a -= b;

		EXPECT_EQ(expected, result);
	}

	{
		int64_t aT = 32424;
		int64_t bT = -12345;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = aT - bT;
		auto& result = a -= b;

		EXPECT_EQ(expected, result);
	}

	{
		BigInt_t a = 0;
		BigInt_t b = 5;

		auto expected = -5;
		auto& result = a -= b;

		EXPECT_EQ(expected, result);
	}

	{
		BigInt_t a = { {1, 1 }, false };
		BigInt_t b = { {2, 1}, false };

		BigInt_t expected = { {1}, true };
		auto& result = a -= b;

		EXPECT_EQ(expected, result);
	}

	{
		/*uint32_t t1 = 0b110000011110011110;
		uint32_t t2 = 0b1000110000010110011011;
		uint32_t t4 = 0b111111111110111111101;

		const auto t3 = t2 - t1;*/
			
		BigInt<int32_t, 2> a =			{ {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int32_t, 2> b =			{ {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<int32_t, 2> expected1 =	{ {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, true };
		BigInt<int32_t, 2> expected2 = -2096637;
		
		ASSERT_EQ(expected1, expected2);

		auto& result = a -= b;

		EXPECT_EQ(expected1, result);
		EXPECT_EQ(expected2, result);
	}

	{
		BigInt<int8_t, 2> a =			{ {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int8_t, 2> b =			{ {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<int8_t, 2> expected1 =	{ {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, true };
		BigInt<int8_t, 2> expected2 = -2096637;

		ASSERT_EQ(expected1, expected2);

		auto& result = a -= b;

		EXPECT_EQ(expected1, result);
		EXPECT_EQ(expected2, result);
	}


	{
		int64_t aT = -12765;
		int64_t bT = -5954;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = BigInt<int64_t, 10ULL>{ aT - bT };
		auto& result = a -= b;

		EXPECT_EQ(expected, result);
	}


	{
		// Create randomizer
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int16_t> dis(std::numeric_limits<int16_t>::min() / 2, std::numeric_limits<int16_t>::max() / 2);

		/// RANDOM TEST
		for (size_t i = 0; i < 1000; i++)
		{
			auto aV = dis(gen);
			auto bV = dis(gen);

			BigInt<int16_t, 10> a = aV;
			BigInt<int16_t, 10> b = bV;

			auto expectedVal = aV - bV;
			BigInt<int16_t, 10> expected = expectedVal;
			auto& result = a -= b;

			bool test = expected == result;

			ASSERT_EQ(expected, result) << "Values were: " << aV << " and " << bV;
		}
	}
}

TEST(BasicArithmaticTests, Subtraction)
{
	{
		int64_t aT = 32424;
		int64_t bT = 12345;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = aT - bT;
		auto result = a - b;

		EXPECT_EQ(expected, result);
	}

	{
		int64_t aT = -32424;
		int64_t bT = 12345;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = aT - bT;
		auto result = a - b;

		EXPECT_EQ(expected, result);
	}

	{
		int64_t aT = 32424;
		int64_t bT = -12345;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = aT - bT;
		auto result = a - b;

		EXPECT_EQ(expected, result);
	}

	{
		BigInt_t a = 0;
		BigInt_t b = 5;

		auto expected = -5;
		auto result = a - b;

		EXPECT_EQ(expected, result);
	}

	{
		BigInt_t a = { {1, 1 }, false };
		BigInt_t b = { {2, 1}, false };

		BigInt_t expected = { {1}, true };
		auto result = a - b;

		EXPECT_EQ(expected, result);
	}

	{
		/*uint32_t t1 = 0b110000011110011110;
		uint32_t t2 = 0b1000110000010110011011;
		uint32_t t4 = 0b111111111110111111101;

		const auto t3 = t2 - t1;*/

		BigInt<int32_t, 2> a = { {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int32_t, 2> b = { {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<int32_t, 2> expected1 = { {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, true };
		BigInt<int32_t, 2> expected2 = -2096637;

		ASSERT_EQ(expected1, expected2);

		auto result = a - b;

		EXPECT_EQ(expected1, result);
		EXPECT_EQ(expected2, result);
	}

	{
		BigInt<int8_t, 2> a = { {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1} };
		BigInt<int8_t, 2> b = { {1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1} };

		BigInt<int8_t, 2> expected1 = { {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, true };
		BigInt<int8_t, 2> expected2 = -2096637;

		ASSERT_EQ(expected1, expected2);

		auto result = a - b;

		EXPECT_EQ(expected1, result);
		EXPECT_EQ(expected2, result);
	}


	{
		int64_t aT = 10391;
		int64_t bT = 450;

		BigInt<int64_t, 10ULL> a = aT;
		BigInt<int64_t, 10ULL> b = bT;

		auto expected = BigInt<int64_t, 10ULL>{ aT - bT };
		auto result = a - b;

		EXPECT_EQ(expected, result);
	}


	{
		// Create randomizer
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int16_t> dis(std::numeric_limits<int16_t>::min() / 2, std::numeric_limits<int16_t>::max() / 2);

		/// RANDOM TEST
		for (size_t i = 0; i < 10000; i++)
		{
			auto aV = dis(gen);
			auto bV = dis(gen);

			BigInt<int16_t, 10> a = aV;
			BigInt<int16_t, 10> b = bV;

			auto expectedVal = aV - bV;
			BigInt<int16_t, 10> expected = expectedVal;
			auto result = a - b;

			bool test = expected == result;

			ASSERT_EQ(expected, result) << "Values were: " << aV << " and " << bV;
		}
	}
}