#include <gtest/gtest.h>

#include <suurimath.h>

#include <random>
#include <cmath>
#include <limits>

using namespace suuri;

TEST(ConversionTests, ConvertionToString)
{
	//// Test specific big values
	//{
	//	BigInt_t testInt = { {0, 1, 40} };

	//	std::string expected = "8630986354536449692464364839029663282043";
	//	std::string result = testInt.str();

	//	EXPECT_EQ(expected, result);

	//	// #####
	//	testInt = { {0, 1, 4, 0, 0, 0, 1000000000325} };

	//	expected = "460462683626499481794456156897130151325232476122970321033410208034425961551349459417219212664895413617529704050257810743656516";
	//	result = testInt.str();

	//	EXPECT_EQ(expected, result);

	//	// #####
	//	testInt = { {0, 1, 4} };

	//	expected = "462789226864979795274364839029663282043";
	//	result = testInt.str();

	//	EXPECT_EQ(expected, result);
	//}

	////// Test base 10 values
	//{
	//	BigInt<int64_t, 10> testInt = { {0, 1, 9} };

	//	std::string expected = "910";
	//	std::string result = testInt.str();

	//	EXPECT_EQ(expected, result);

	//	// #####
	//	testInt = 32567;

	//	expected = "32567";
	//	result = testInt.str();

	//	EXPECT_EQ(expected, result);
	//}

	//// Test random uint64_t numbers
	//{
	//	// Create randomizer
	//	std::random_device rd;
	//	std::mt19937 gen(rd());
	//	std::uniform_int_distribution<uint64_t> dist(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());

	//	// Create the big num
	//	for (size_t i = 0; i < 100; i++)
	//	{
	//		auto randToTest = dist(gen);
	//		BigInt_t testInt = randToTest;

	//		std::string expected = std::to_string(randToTest);
	//		std::string result = testInt.str();

	//		ASSERT_EQ(expected, result);
	//	}
	//}
}


TEST(ConversionTests, CastTest)
{
	//// Test base 10 values
	{
		BigInt10_t testInt = { {0, 1, 9} };

		EXPECT_EQ(testInt.cast<int>(), 910);
		EXPECT_EQ(testInt.cast_unsafe<int>(), 910);

		// #####
		testInt = 32567;

		EXPECT_EQ(testInt.cast<int>(), 32567);
		EXPECT_EQ(testInt.cast_unsafe<int>(), 32567);
	}

	//// Test throws
	{
		BigInt_t test = { {1, 1, 1, 1, 1} };

		EXPECT_THROW(test.cast<int>(), std::overflow_error);
	}

	//// Test throws
	{
		BigInt_t test = { {1, 1, 1, 1, 1}, true };

		EXPECT_THROW(test.cast<int>(), std::underflow_error);
	}
}

TEST(ConversionTests, CastToOtherBigInt)
{

	{
		uint64_t testInt = 255;
		BigInt10_t a = testInt;
		BigInt16_t b = testInt;
		BigInt2_t c = testInt;
		BigInt_t d = testInt;

		// Test a equals all others
		EXPECT_EQ(a.cast_bigint<BigInt16_t>(), b);
		EXPECT_EQ(a.cast_bigint<BigInt2_t>(), c);
		EXPECT_EQ(a.cast_bigint<BigInt_t>(), d);

		// Test b equals all others
		EXPECT_EQ(b.cast_bigint<BigInt10_t>(), a);
		EXPECT_EQ(b.cast_bigint<BigInt2_t>(), c);
		EXPECT_EQ(b.cast_bigint<BigInt_t>(), d);

		// Test c equals all others
		EXPECT_EQ(c.cast_bigint<BigInt16_t>(), b);
		EXPECT_EQ(c.cast_bigint<BigInt10_t>(), a);
		EXPECT_EQ(c.cast_bigint<BigInt_t>(), d);

		// Test d equals all others
		EXPECT_EQ(d.cast_bigint<BigInt16_t>(), b);
		EXPECT_EQ(d.cast_bigint<BigInt2_t>(), c);
		EXPECT_EQ(d.cast_bigint<BigInt10_t>(), a);
	}

}

