#include <gtest/gtest.h>

#include "test_helpers.hpp"

TEST (IntAddition, IntegersPositivePositive)
{
	// Test addition of small integers (result should be less than 1073741824)
	{
		su::big_int_t a = 0;
		su::big_int_t b = 0;
		su::big_int_t c = a + b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = 0;
		c = a + b;

		EXPECT_EQ(c, 1);

		a = 0;
		b = 1;
		c = a + b;

		EXPECT_EQ(c, 1);

		a = 1;
		b = 1;
		c = a + b;

		EXPECT_EQ(c, 2);

		a = 1;
		b = 2;
		c = a + b;

		EXPECT_EQ(c, 3);

		a = 2;
		b = 1;
		c = a + b;

		EXPECT_EQ(c, 3);

		a = 536870911;
		b = 536870911;
		c = a + b;

		EXPECT_EQ(c, 1073741822);

		a = 536870911;
		b = 536870911;
		c = a + b;

		EXPECT_EQ(c, 1073741822);

		a = 11111;
		b = 1111111112;
		c = a + b;

		EXPECT_EQ(c, 1111122223);

		// Also test a few with reversed lhs and rhs

		a = 536870911;
		b = 536870911;
		c = b + a;

		EXPECT_EQ(c, 1073741822);

		a = 536870911;
		b = 536870911;
		c = b + a;

		EXPECT_EQ(c, 1073741822);

		a = 11111;
		b = 1111111112;
		c = b + a;

		EXPECT_EQ(c, 1111122223);
	}

	// Test addition of small integers (result should be less than 2^60)
	{
		su::big_int_t a = 123456789;
		su::big_int_t b = 987654321;
		su::big_int_t c = a + b;

		EXPECT_EQ(c, 1111111110);

		a = 2147483647;
		b = 1;
		c = a + b;

		EXPECT_EQ(c, 2147483648);

		a = 2147483647;
		b = 2;
		c = a + b;

		EXPECT_EQ(c, 2147483649);

		a = 2147483647;
		b = 2147483647;
		c = a + b;

		EXPECT_EQ(c, 4294967294);

		a = 576460752303423480ULL;
		b = 576460752303423480ULL;
		c = a + b;

		EXPECT_EQ(c, 1152921504606846960ULL);

		// Also test some in reverse lhs and rhs

		a = 123456789;
		b = 987654321;
		c = b + a;

		EXPECT_EQ(c, 1111111110);

		a = 2147483647;
		b = 1;
		c = b + a;

		EXPECT_EQ(c, 2147483648);

		a = 2147483647;
		b = 2;
		c = b + a;

		EXPECT_EQ(c, 2147483649);
	}

	// Test addition of large integers (using string initializer)
	{
		su::big_int_t a = su::big_int_t("123456789123456789123456789123456789");
		su::big_int_t b = su::big_int_t("987654321987654321987654321987654321");
		su::big_int_t c = a + b;

		EXPECT_EQ(c, su::big_int_t("1111111111111111111111111111111111110"));

		a = su::big_int_t("18446744073709551615");
		b = su::big_int_t("18446744073709551615");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("36893488147419103230"));

		a = su::big_int_t("18446744073709551615");
		b = su::big_int_t("5215321523512");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("18446749289031075127"));

		a = su::big_int_t("999999999999999999999999");
		b = su::big_int_t("1");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("1000000000000000000000000"));

		a = su::big_int_t("999999999999999999999999");
		b = su::big_int_t("999999999999999999999991");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("1999999999999999999999990"));

		a = su::big_int_t("1329227995784915872903807060278812422");
		b = su::big_int_t("1329227995784915872903690623925709942");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("2658455991569831745807497684204522364"));
	}
}

TEST (IntAddition, IntegersNegativeNegative)
{
	// These are just the positive positive tests with a negative sign.

	// Test addition of small integers (result should be less than 1073741824)
	{
		su::big_int_t a = 0;
		su::big_int_t b = 0;
		su::big_int_t c = a + b;

		EXPECT_EQ(c, 0);

		a = -1;
		b = 0;
		c = a + b;

		EXPECT_EQ(c, -1);

		a = 0;
		b = -1;
		c = a + b;

		EXPECT_EQ(c, -1);

		a = -1;
		b = -1;
		c = a + b;

		EXPECT_EQ(c, -2);

		a = -1;
		b = -2;
		c = a + b;

		EXPECT_EQ(c, -3);

		a = -2;
		b = -1;
		c = a + b;

		EXPECT_EQ(c, -3);

		a = -536870911;
		b = -536870911;
		c = a + b;

		EXPECT_EQ(c, -1073741822);

		a = -11111;
		b = -1111111112;
		c = a + b;

		EXPECT_EQ(c, -1111122223);

		// Also test a few with reversed lhs and rhs

		a = -536870911;
		b = -536870911;
		c = b + a;

		EXPECT_EQ(c, -1073741822);

		a = -11111;
		b = -1111111112;
		c = b + a;

		EXPECT_EQ(c, -1111122223);
	}

	// Test addition of small integers (result should be less than 2^60)
	{
		su::big_int_t a = -123456789;
		su::big_int_t b = -987654321;
		su::big_int_t c = a + b;

		EXPECT_EQ(c, -1111111110);

		a = -2147483647;
		b = -1;
		c = a + b;

		EXPECT_EQ(c, -2147483648LL);

		a = -2147483647LL;
		b = 2;
		c = a + b;

		EXPECT_EQ(c, -2147483645LL);

		a = -2147483647;
		b = -2147483647;
		c = a + b;

		EXPECT_EQ(c, -4294967294LL);

		a = -576460752303423480LL;
		b = -576460752303423480LL;
		c = a + b;

		EXPECT_EQ(c, -1152921504606846960LL);

		// Also test some in reverse lhs and rhs

		a = -123456789;
		b = -987654321;
		c = b + a;

		EXPECT_EQ(c, -1111111110);

		a = -2147483647;
		b = -1;
		c = b + a;

		EXPECT_EQ(c, -2147483648);

		a = -2147483647;
		b = -2;
		c = b + a;

		EXPECT_EQ(c, -2147483649);
	}

	// Test addition of large integers (using string initializer)
	{
		su::big_int_t a = su::big_int_t("-123456789123456789123456789123456789");
		su::big_int_t b = su::big_int_t("-987654321987654321987654321987654321");
		su::big_int_t c = a + b;

		EXPECT_EQ(c, su::big_int_t("-1111111111111111111111111111111111110"));

		a = su::big_int_t("-18446744073709551615");
		b = su::big_int_t("-18446744073709551615");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("-36893488147419103230"));

		a = su::big_int_t("-18446744073709551615");
		b = su::big_int_t("-5215321523512");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("-18446749289031075127"));

		a = su::big_int_t("-999999999999999999999999");
		b = su::big_int_t("-1");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("-1000000000000000000000000"));

		a = su::big_int_t("-999999999999999999999999");
		b = su::big_int_t("-999999999999999999999991");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("-1999999999999999999999990"));

		a = su::big_int_t("-1329227995784915872903807060278812422");
		b = su::big_int_t("-1329227995784915872903690623925709942");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("-2658455991569831745807497684204522364"));
	}
}

TEST (IntAddition, IntegersPositiveNegative)
{
	// Also negative positive

	// Test addition of small integers
	{
		su::big_int_t a = 0;
		su::big_int_t b = 0;
		su::big_int_t c = a + b;

		EXPECT_EQ(c, 0);

		a = -1;
		b = 0;
		c = a + b;

		EXPECT_EQ(c, -1);

		a = 0;
		b = -1;
		c = a + b;

		EXPECT_EQ(c, -1);

		a = -1;
		b = 1;
		c = a + b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = -2;
		c = a + b;

		EXPECT_EQ(c, -1);

		a = 2;
		b = -1;
		c = a + b;

		EXPECT_EQ(c, 1);

		a = 536870911;
		b = -536870911;
		c = a + b;

		EXPECT_EQ(c, 0);

		a = 11111;
		b = -1111111112;
		c = a + b;

		EXPECT_EQ(c, -1111100001);

		a = -11111;
		b = 1111111112;
		c = a + b;

		EXPECT_EQ(c, 1111100001);

		// Also test a few with reversed lhs and rhs

		a = 536870911;
		b = -536870911;
		c = b + a;

		EXPECT_EQ(c, 0);

		a = 11111;
		b = -1111111112;
		c = b + a;

		EXPECT_EQ(c, -1111100001);
	}

	// Test addition of small integers
	{
		su::big_int_t a = 123456789;
		su::big_int_t b = -987654321;
		su::big_int_t c = a + b;

		EXPECT_EQ(c, -864197532);

		a = -2147483647;
		b = 1;
		c = a + b;

		EXPECT_EQ(c, -2147483646);

		a = 2147483647;
		b = -2;
		c = a + b;

		EXPECT_EQ(c, 2147483645);

		a = -2147483647;
		b = 2147483647;
		c = a + b;

		EXPECT_EQ(c, 0);

		a = -576460752303423480LL;
		b = 576460752303423480LL;
		c = a + b;

		EXPECT_EQ(c, 0);

		a = 132922799578491587LL;
		b = -132922799578491529LL;
		c = a + b;

		EXPECT_EQ(c, 58);
	}

	// Test addition of large integers (using string initializer)
	{

		su::big_int_t a = su::big_int_t("123456789123456789123456789123456789");
		su::big_int_t b = su::big_int_t("-987654321987654321987654321987654321");
		su::big_int_t c = a + b;

		EXPECT_EQ(c, su::big_int_t("-864197532864197532864197532864197532"));

		a = su::big_int_t("18446744073709551615");
		b = su::big_int_t("-18446744073709551615");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("0"));

		a = su::big_int_t("-18446744073709551615");
		b = su::big_int_t("5215321523512");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("-18446738858388028103"));

		a = su::big_int_t("999999999999999999999999");
		b = su::big_int_t("-1");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("999999999999999999999998"));

		a = su::big_int_t("-999999999999999999999999");
		b = su::big_int_t("999999999999999999999991");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("-8"));

		a = su::big_int_t("1329227995784915872903807060278812422");
		b = su::big_int_t("-1329227995784915872903690623925709942");
		c = a + b;

		EXPECT_EQ(c, su::big_int_t("116436353102480"));
	}
}

TEST (IntAddition, Random)
{
	// Test 8-bit integer as input
	run_pre_generated_test_file_bin_op<int8_t>(
			"../../random_tests/int/addition/addition_8bit_input.test",
			[](const su::big_int_t& a, const su::big_int_t& b) { return a + b; });

	// Test 16-bit integer as input
	run_pre_generated_test_file_bin_op<int16_t>(
			"../../random_tests/int/addition/addition_16bit_input.test",
			[](const su::big_int_t& a, const su::big_int_t& b) { return a + b; });

	// Test 32-bit integer as input
	run_pre_generated_test_file_bin_op<int32_t>(
			"../../random_tests/int/addition/addition_32bit_input.test",
			[](const su::big_int_t& a, const su::big_int_t& b) { return a + b; });

	// Test 64-bit integer as input
	run_pre_generated_test_file_bin_op<int64_t>(
			"../../random_tests/int/addition/addition_64bit_input.test",
			[](const su::big_int_t& a, const su::big_int_t& b) { return a + b; });

	// Test large integer as input
	run_pre_generated_test_file_bin_op<std::string, false>(
			"../../random_tests/int/addition/addition_large_input.test",
			[](const su::big_int_t& a, const su::big_int_t& b) { return a + b; });
}
