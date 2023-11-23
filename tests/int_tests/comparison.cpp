#include <gtest/gtest.h>

#include <big_int.hpp>


namespace su = suuri;

TEST (IntComparison, Equality)
{
	// Test self equality
	{
		su::big_int_t a = {};
		ASSERT_EQ(a, a);
		
		a = 1;
		ASSERT_EQ(a, a);
		
		a = -1;
		ASSERT_EQ(a, a);
	}
	
	// Test different objects with same value are equal (also with reverse lhs and rhs)
	{
		su::big_int_t a = {};
		su::big_int_t b = {};
		ASSERT_EQ(a, b);
		ASSERT_EQ(b, a);
		
		a = 1;
		b = 1;
		ASSERT_EQ(a, b);
		ASSERT_EQ(b, a);
		
		a = -1;
		b = -1;
		ASSERT_EQ(a, b);
		ASSERT_EQ(b, a);
	}
	
	// Test that big numbers are also equal (bigger than 2^128)
	{
		// Create vector for storing the digits (each digit should be base more than 2^30, so let's use 6 digits)
		std::vector<su::digit_t> digits = {0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff};
		
		// Initialise the big int explicitly and do tests.
		su::big_int_t a = su::big_int_t(digits);
		ASSERT_EQ(a, a);
		
		// Also test the negation
		su::big_int_t b = -a;
		ASSERT_EQ(b, b);
		
		// And also test non equality of the negation
		ASSERT_NE(a, b);
	}
	
	// Test not equality (and also check reverse of lhs and rhs)
	{
		su::big_int_t a = {};
		su::big_int_t b = 1;
		ASSERT_NE(a, b);
		ASSERT_NE(b, a);
		
		a = 1;
		b = 2;
		ASSERT_NE(a, b);
		ASSERT_NE(b, a);
		
		a = -1;
		b = 1;
		ASSERT_NE(a, b);
		ASSERT_NE(b, a);
	}
};