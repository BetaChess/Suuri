#include <gtest/gtest.h>

#include <big_int.hpp>

namespace su = suuri;

TEST(IntMultiplication, IntegersPositivePositive)
{
	// Test multiplication of small integers (result should be less than 1073741824)
	{
		su::big_int_t a = 0;
		su::big_int_t b = 0;
		su::big_int_t c = a * b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = 0;
		c = a * b;

		EXPECT_EQ(c, 0);

		a = 0;
		b = 1;
		c = a * b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = 1;
		c = a * b;

		EXPECT_EQ(c, 1);

		a = 1;
		b = 2;
		c = a * b;

		EXPECT_EQ(c, 2);

		a = 2;
		b = 1;
		c = a * b;

		EXPECT_EQ(c, 2);

		// Larger but still small integers
		a = 50;
		b = 50;
		c = a * b;
		
		EXPECT_EQ(c, 2500);
		
		a = 256;
		b = 256;
		c = a * b;
		
		EXPECT_EQ(c, 65536);
		
		a = 65536;
		b = 65536;
		c = a * b;
		
		EXPECT_EQ(c, 4294967296);
		
		a = 433;
		b = 129;
		c = a * b;
		
		EXPECT_EQ(c, 55857);
	}
	
	// Test multiplication of large integers
	{
		su::big_int_t a = 536870911;
		su::big_int_t b = 536870911;
		su::big_int_t c = a * b;
		
		EXPECT_EQ(c, 288230375077969921LL);

		a = 11111;
		b = 1111111112;
		c = a * b;

		EXPECT_EQ(c, 12345555565432LL);
	}
	
	// Test of large integers (using string initializer)
	{
		su::big_int_t a = su::big_int_t("123456789123456789123456789123456789");
		su::big_int_t b = su::big_int_t("987654321987654321987654321987654321");
		su::big_int_t c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("121932631356500531591068431825636331816338969581771069347203169112635269"));
		
		a = su::big_int_t("576460752303423488");
		b = su::big_int_t("576460752303423488");
		c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("332306998946228968225951765070086144"));
		
		a = su::big_int_t("132922799578491587");
		b = su::big_int_t("132922799578491587");
		c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("17668470647783843218636542229778569"));
	}
}

TEST(IntMultiplication, IntegersNegativeNegative)
{
	// Test multiplication of small integers (result should be less than 1073741824)
	{
		su::big_int_t a = -0;
		su::big_int_t b = -0;
		su::big_int_t c = a * b;

		EXPECT_EQ(c, 0);

		a = -1;
		b = -0;
		c = a * b;

		EXPECT_EQ(c, 0);

		a = -0;
		b = -1;
		c = a * b;

		EXPECT_EQ(c, 0);

		a = -1;
		b = -1;
		c = a * b;

		EXPECT_EQ(c, 1);

		a = -1;
		b = -2;
		c = a * b;

		EXPECT_EQ(c, 2);

		a = -2;
		b = -1;
		c = a * b;

		EXPECT_EQ(c, 2);

		// Larger but still small integers
		a = -50;
		b = -50;
		c = a * b;
		
		EXPECT_EQ(c, 2500);
		
		a = -256;
		b = -256;
		c = a * b;
		
		EXPECT_EQ(c, 65536);
		
		a = -65536;
		b = -65536;
		c = a * b;
		
		EXPECT_EQ(c, 4294967296);
		
		a = -433;
		b = -129;
		c = a * b;
		
		EXPECT_EQ(c, 55857);
	}
	
	// Test multiplication of large integers
	{
		su::big_int_t a = -536870911;
		su::big_int_t b = -536870911;
		su::big_int_t c = a * b;
		
		EXPECT_EQ(c, 288230375077969921LL);

		a = -11111;
		b = -1111111112;
		c = a * b;

		EXPECT_EQ(c, 12345555565432LL);
	}
	
	// Test of large integers (using string initializer)
	{
		su::big_int_t a = su::big_int_t("-123456789123456789123456789123456789");
		su::big_int_t b = su::big_int_t("-987654321987654321987654321987654321");
		su::big_int_t c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("121932631356500531591068431825636331816338969581771069347203169112635269"));
		
		a = su::big_int_t("-576460752303423488");
		b = su::big_int_t("-576460752303423488");
		c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("332306998946228968225951765070086144"));
		
		a = su::big_int_t("-132922799578491587");
		b = su::big_int_t("-132922799578491587");
		c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("17668470647783843218636542229778569"));
	}
}

TEST(IntMultiplication, IntegersPositiveNegative)
{
	// Test multiplication of small integers (result should be less than 1073741824)
	{
		su::big_int_t a = 0;
		su::big_int_t b = -0;
		su::big_int_t c = a * b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = -0;
		c = a * b;

		EXPECT_EQ(c, 0);

		a = 0;
		b = -1;
		c = a * b;

		EXPECT_EQ(c, 0);

		a = 1;
		b = -1;
		c = a * b;

		EXPECT_EQ(c, -1);

		a = 1;
		b = -2;
		c = a * b;

		EXPECT_EQ(c, -2);

		a = 2;
		b = -1;
		c = a * b;

		EXPECT_EQ(c, -2);

		// Larger but still small integers
		a = 50;
		b = -50;
		c = a * b;
		
		EXPECT_EQ(c, -2500);
		
		a = 256;
		b = -256;
		c = a * b;
		
		EXPECT_EQ(c, -65536);
		
		a = 65536;
		b = -65536;
		c = a * b;
		
		EXPECT_EQ(c, -4294967296);
		
		a = 433;
		b = -129;
		c = a * b;
		
		EXPECT_EQ(c, -55857);
	}
	
	// Test multiplication of large integers
	{
		su::big_int_t a = 536870911;
		su::big_int_t b = -536870911;
		su::big_int_t c = a * b;
		
		EXPECT_EQ(c, -288230375077969921LL);

		a = 11111;
		b = -1111111112;
		c = a * b;

		EXPECT_EQ(c, -12345555565432LL);
	}
	
	// Test of large integers (using string initializer)
	{
		su::big_int_t a = su::big_int_t("123456789123456789123456789123456789");
		su::big_int_t b = su::big_int_t("-987654321987654321987654321987654321");
		su::big_int_t c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("-121932631356500531591068431825636331816338969581771069347203169112635269"));
		
		a = su::big_int_t("576460752303423488");
		b = su::big_int_t("-576460752303423488");
		c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("-332306998946228968225951765070086144"));
		
		a = su::big_int_t("132922799578491587");
		b = su::big_int_t("-132922799578491587");
		c = a * b;
		
		EXPECT_EQ(c, su::big_int_t("-17668470647783843218636542229778569"));
	}
}
