#include "test_helpers.hpp"


#include <gtest/gtest.h>

#include <big_int.hpp>
#include <random>

namespace su = suuri;

TEST (IntDivision, IntergerPositivePositve)
{
	// Test division of small integers
	{
		su::big_int_t a = 0;
		su::big_int_t b = 1;
		su::big_int_t c = a / b;
		su::big_int_t d = a % b;

		EXPECT_EQ(c, 0);
		EXPECT_EQ(d, 0);

		a = 1;
		b = 1;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1);
		EXPECT_EQ(d, 0);

		a = 1;
		b = 2;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 0);
		EXPECT_EQ(d, 1);

		a = 2;
		b = 1;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 2);
		EXPECT_EQ(d, 0);

		// Larger but still small integers
		a = 50;
		b = 50;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1);
		EXPECT_EQ(d, 0);

		a = 256;
		b = 256;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1);
		EXPECT_EQ(d, 0);

		a = 65536;
		b = 65536;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1);
		EXPECT_EQ(d, 0);

		a = 123456789;
		b = 9876;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 12500);
		EXPECT_EQ(d, 6789);

		a = 7859278;
		b = 7;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1122754);
		EXPECT_EQ(d, 0);
	}

	// Test division of larger integers
	{
		su::big_int_t a = su::big_int_t("785927855555555555666665");
		su::big_int_t b = 7;
		su::big_int_t c = a / b;
		su::big_int_t d = a % b;

		EXPECT_EQ(c, su::big_int_t("112275407936507936523809"));
		EXPECT_EQ(d, 2);


		a = su::big_int_t("785927855555555555666665");
		b = su::big_int_t("812093423214");
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, su::big_int_t("967780101512"));
		EXPECT_EQ(d, su::big_int_t("283058367097"));


		a = su::big_int_t("9999999999999999999999");
		b = su::big_int_t("9999999999");
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, su::big_int_t("1000000000100"));
		EXPECT_EQ(d, su::big_int_t("99"));


		a = su::big_int_t("427488328406002556429801375338939964969034378836681372467200000000");
		b = 10;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, su::big_int_t("42748832840600255642980137533893996496903437883668137246720000000"));
		EXPECT_EQ(d, 0);
	}
}

TEST (IntDivision, IntergerPositiveNegative)
{
	// Test division of small integers
	{
		su::big_int_t a = 0;
		su::big_int_t b = -1;
		su::big_int_t c = a / b;
		su::big_int_t d = a % b;

		EXPECT_EQ(c, 0);
		EXPECT_EQ(d, 0);


		a = -1;
		b = 1;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, -1);
		EXPECT_EQ(d, 0);


		a = 1;
		b = -2;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 0);
		EXPECT_EQ(d, 1);


		a = 2;
		b = -1;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, -2);
		EXPECT_EQ(d, 0);


		// Larger but still small integers
		a = -50;
		b = 50;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, -1);
		EXPECT_EQ(d, 0);


		a = -256;
		b = 256;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, -1);
		EXPECT_EQ(d, 0);


		a = 65536;
		b = -65536;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, -1);
		EXPECT_EQ(d, 0);


		a = -123456789;
		b = 9876;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, -12500);
		EXPECT_EQ(d, -6789);


		a = 7859278;
		b = -7;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, -1122754);
		EXPECT_EQ(d, 0);
	}

	// Test division of larger integers
	{
		su::big_int_t a = su::big_int_t("-785927855555555555666665");
		su::big_int_t b = 7;
		su::big_int_t c = a / b;
		su::big_int_t d = a % b;

		EXPECT_EQ(c, su::big_int_t("-112275407936507936523809"));
		EXPECT_EQ(d, -2);


		a = su::big_int_t("785927855555555555666665");
		b = su::big_int_t("-812093423214");
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, su::big_int_t("-967780101512"));
		EXPECT_EQ(d, su::big_int_t("283058367097"));


		a = su::big_int_t("9999999999999999999999");
		b = su::big_int_t("-9999999999");
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, su::big_int_t("-1000000000100"));
		EXPECT_EQ(d, su::big_int_t("99"));
	}
}

TEST (IntDivision, IntergerNegativeNegative)
{
	// Test division of small integers
	{
		su::big_int_t a = 0;
		su::big_int_t b = -1;
		su::big_int_t c = a / b;
		su::big_int_t d = a % b;

		EXPECT_EQ(c, 0);
		EXPECT_EQ(d, 0);

		a = -1;
		b = -1;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1);
		EXPECT_EQ(d, 0);

		a = -1;
		b = -2;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 0);
		EXPECT_EQ(d, -1);

		a = -2;
		b = -1;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 2);
		EXPECT_EQ(d, 0);

		// Larger but still small integers
		a = -50;
		b = -50;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1);
		EXPECT_EQ(d, 0);

		a = -256;
		b = -256;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1);
		EXPECT_EQ(d, 0);

		a = -65536;
		b = -65536;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1);
		EXPECT_EQ(d, 0);

		a = -123456789;
		b = -9876;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 12500);
		EXPECT_EQ(d, -6789);

		a = -7859278;
		b = -7;
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, 1122754);
		EXPECT_EQ(d, 0);
	}

	// Test division of larger integers
	{
		su::big_int_t a = su::big_int_t("-785927855555555555666665");
		su::big_int_t b = -7;
		su::big_int_t c = a / b;
		su::big_int_t d = a % b;

		EXPECT_EQ(c, su::big_int_t("112275407936507936523809"));
		EXPECT_EQ(d, -2);


		a = su::big_int_t("-785927855555555555666665");
		b = su::big_int_t("-812093423214");
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, su::big_int_t("967780101512"));
		EXPECT_EQ(d, su::big_int_t("-283058367097"));


		a = su::big_int_t("-9999999999999999999999");
		b = su::big_int_t("-9999999999");
		c = a / b;
		d = a % b;

		EXPECT_EQ(c, su::big_int_t("1000000000100"));
		EXPECT_EQ(d, su::big_int_t("-99"));
	}
}

TEST (IntDivision, Special)
{
	// Test that division by zero gives an exception and keeps the values unchanged
	{
		su::big_int_t a = 1;
		su::big_int_t b = 0;

		EXPECT_THROW(a / b, su::divide_by_zero);
		EXPECT_THROW(a % b, su::divide_by_zero);
		EXPECT_EQ(a, 1);
		EXPECT_EQ(b, 0);

		a = 0;
		b = 0;

		EXPECT_THROW(a / b, su::divide_by_zero);
		EXPECT_THROW(a % b, su::divide_by_zero);
		EXPECT_EQ(a, 0);
		EXPECT_EQ(b, 0);

		a = -1;
		b = 0;

		EXPECT_THROW(a / b, su::divide_by_zero);
		EXPECT_THROW(a % b, su::divide_by_zero);
		EXPECT_EQ(a, -1);
		EXPECT_EQ(b, 0);

		// And test a few random values
		// Random generator
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1000000000);

		su::big_int_t a_cp;
		for (int i = 0; i < 100; i++)
		{
			a = dis(gen);
			a_cp = a;
			b = 0;

			ASSERT_THROW(a / b, su::divide_by_zero);
			EXPECT_THROW(a % b, su::divide_by_zero);
			ASSERT_EQ(a, a_cp);
			ASSERT_EQ(b, 0);
		}
	}
}

TEST (IntDivision, Random)
{
	auto binOp = [](const su::big_int_t &a, const su::big_int_t &b) { return a / b; };

	// Test 8-bit integer as input
	run_pre_generated_test_file_bin_op<int8_t>(
			"../../random_tests/int/division/division_8bit_input.test",
			binOp);

	// Test 16-bit integer as input
	run_pre_generated_test_file_bin_op<int16_t>(
			"../../random_tests/int/division/division_16bit_input.test",
			binOp);

	// Test 32-bit integer as input
	run_pre_generated_test_file_bin_op<int32_t>(
			"../../random_tests/int/division/division_32bit_input.test",
			binOp);

	// Test 64-bit integer as input
	run_pre_generated_test_file_bin_op<int64_t>(
			"../../random_tests/int/division/division_64bit_input.test",
			binOp);

	// Test large integer as input
	run_pre_generated_test_file_bin_op<std::string, false>(
			"../../random_tests/int/division/division_large_input.test",
			binOp);
}
