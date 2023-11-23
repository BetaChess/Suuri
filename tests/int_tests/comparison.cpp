#include <gtest/gtest.h>

#include <big_int.hpp>


namespace su = suuri;

TEST (IntComparison, Equality)
{
	// Test self equality
	{
		su::big_int_t a = {};
		EXPECT_EQ(a, a);
		
		a = 1;
		EXPECT_EQ(a, a);
		
		a = -1;
		EXPECT_EQ(a, a);
	}
	
	// Test different objects with same value are equal (also with reverse lhs and rhs)
	{
		su::big_int_t a = {};
		su::big_int_t b = {};
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		
		a = 1;
		b = 1;
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		
		a = -1;
		b = -1;
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
	}
	
	// Test that big numbers are also equal (bigger than 2^128)
	{
		// Create vector for storing the digits (each digit should be base more than 2^30, so let's use 6 digits)
		std::vector<su::digit_t> digits = {0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff};
		
		// Initialise the big int explicitly and do tests.
		su::big_int_t a = su::big_int_t(digits);
		EXPECT_EQ(a, a);
		
		// Also test the negation
		su::big_int_t b = -a;
		EXPECT_EQ(b, b);
		
		// And also test non equality of the negation
		EXPECT_NE(a, b);
	}
	
	// Test not equality (and also check reverse of lhs and rhs)
	{
		su::big_int_t a = {};
		su::big_int_t b = 1;
		EXPECT_NE(a, b);
		EXPECT_NE(b, a);
		
		a = 1;
		b = 2;
		EXPECT_NE(a, b);
		EXPECT_NE(b, a);
		
		a = -1;
		b = 1;
		EXPECT_NE(a, b);
		EXPECT_NE(b, a);
	}
};

// Also test lessequal and greaterequal
TEST (IntComparison, LessAndGreater)
{
	// Test self
	{
		su::big_int_t a = {};
		EXPECT_FALSE(a < a);
		EXPECT_LE(a, a);
		EXPECT_FALSE(a > a);
		EXPECT_GE(a, a);
		
		a = 1;
		EXPECT_FALSE(a < a);
		EXPECT_LE(a, a);
		EXPECT_FALSE(a > a);
		EXPECT_GE(a, a);
		
		a = -1;
		EXPECT_FALSE(a < a);
		EXPECT_LE(a, a);
		EXPECT_FALSE(a > a);
		EXPECT_GE(a, a);
		
		// Also test big values
		// Create vector for storing the digits
		su::digit_storage_t digits = {0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff};
		a = su::big_int_t(std::move(digits));
		EXPECT_FALSE(a < a);
		EXPECT_LE(a, a);
		EXPECT_FALSE(a > a);
		EXPECT_GE(a, a);
	}
	
	// Test different objects with same value
	{
		su::big_int_t a = {};
		su::big_int_t b = {};
		EXPECT_FALSE(a < b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(a > b);
		EXPECT_GE(a, b);
		
		a = 1;
		b = 1;
		EXPECT_FALSE(a < b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(a > b);
		EXPECT_GE(a, b);
		
		a = -1;
		b = -1;
		EXPECT_FALSE(a < b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(a > b);
		EXPECT_GE(a, b);
		
		// Also test big values
		// Create vector for storing the digits
		su::digit_storage_t digits = {0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff};
		a = su::big_int_t(digits);
		b = su::big_int_t(digits);
		EXPECT_FALSE(a < b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(a > b);
		EXPECT_GE(a, b);
		
		a = b;
		EXPECT_FALSE(a < b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(a > b);
		EXPECT_GE(a, b);
	}
	
	// Test non equal values
	{
		su::big_int_t a = {};
		su::big_int_t b = 1;
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);

		a = 1;
		b = 2;
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);

		a = -1;
		b = 1;
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);

		a = -2;
		b = -1;
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);

		// Test other small values below 2^30
		a = 0x7fffffff;
		b = 0x80000000;
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);

		a = -0x80000000L;
		b = -0x7fffffff;
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);

		// Test big values
		a = su::big_int_t(su::digit_storage_t{0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xeeeeeeee});
		b = su::big_int_t(su::digit_storage_t{0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff});
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);
		
		a = su::big_int_t(su::digit_storage_t{0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff}, true);
		b = su::big_int_t(su::digit_storage_t{0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xeeeeeeee}, true);
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);
		
		a = su::big_int_t(su::digit_storage_t{0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xcccccccc, 0xeeeeeeee, 0xffffffff});
		b = su::big_int_t(su::digit_storage_t{0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff});
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);
		
		a = su::big_int_t(su::digit_storage_t{0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff}, true);
		b = su::big_int_t(su::digit_storage_t{0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xcccccccc, 0xeeeeeeee, 0xffffffff}, true);
		EXPECT_LT(a, b);
		EXPECT_LE(a, b);
		EXPECT_FALSE(b < a);
		EXPECT_GT(b, a);
		EXPECT_GE(b, a);
		EXPECT_FALSE(a > b);
	}
}
