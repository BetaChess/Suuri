#include <gtest/gtest.h>

#include <big_int.hpp>


namespace su = suuri;

TEST (IntComparison, Equality)
{
	// Test self equality
	su::BigInt a{};
	ASSERT_EQ(a, a);
	
};