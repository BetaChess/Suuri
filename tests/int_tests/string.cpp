#include <gtest/gtest.h>

#include <big_int.hpp>

#include <sstream>
#include <string>


namespace su = suuri;


TEST(IntString, DirectBase10Constructor)
{
	// Test that small numbers initialised with a string are equal to their builtin primitive counterpart
	su::big_int_t a = 0;
	su::big_int_t b{"0"};
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
	
	a = 1;
	b = su::big_int_t("1");
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
	
	a = -1;
	b = su::big_int_t("-1");
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
	
	a = 123456789;
	b = su::big_int_t("123456789");
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
	
	a = -123456789;
	b = su::big_int_t("-123456789");
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
	
	// Test number bigger than 2^31 and less than 2^32 - 1
	a = 2147483647;
	b = su::big_int_t("2147483647");
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
	
	a = -2147483647;
	b = su::big_int_t("-2147483647");
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
	
	// Also test a 64 unsigned integer
	a = 123456789123456789ULL;
	b = su::big_int_t("123456789123456789");
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
	
	a = 18446744073709551615ULL;
	b = su::big_int_t("18446744073709551615");
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(b, a);
}

TEST(IntString, SpecifiedBaseConstructor)
{
	{
		su::big_int_t a{"0"};
		su::big_int_t b;
		
		for (size_t i = 2; i < 37; i++)
		{
			std::stringstream ss;
			ss << 'b' << i << '_' << '0';
			b = su::big_int_t(ss.str());
			
			EXPECT_EQ(a, b) << "Tested base is: " << i;
			EXPECT_EQ(b, a) << "Tested base is: " << i;;
		}
		
		a = su::big_int_t("1");
		
		for (size_t i = 2; i < 37; i++)
		{
			std::stringstream ss;
			ss << 'b' << i << '_' << '1';
			b = su::big_int_t(ss.str());
			
			EXPECT_EQ(a, b) << "Tested base is: " << i;
			EXPECT_EQ(b, a) << "Tested base is: " << i;;
		}
		
		// Test negative values
		a = su::big_int_t("-1");
		
		for (size_t i = 2; i < 37; i++)
		{
			std::stringstream ss;
			ss << 'b' << i << '_' << "-1";
			b = su::big_int_t(ss.str());
			
			EXPECT_EQ(a, b) << "Tested base is: " << i;
			EXPECT_EQ(b, a) << "Tested base is: " << i;;
		}
		
		// We're going to do the rest of the tests using the number 123456789012345678909876543211234567890
		
		////// Binary (base 2)
		a = su::big_int_t("123456789012345678909876543211234567890");
		b = su::big_int_t("b2_1011100111000001110100110100101011000000001010111111110110001100010001011001110000110011110110100100010101111101010011011010010");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Ternary (base 3)
		b = su::big_int_t("b3_21111222001101112001112201120001100200212102112201220011122121021000210122012200");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Quaternary (base 4)
		b = su::big_int_t("b4_1130320032212211120001113332301202023032012132310202233222123102");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Quinary (base 5)
		b = su::big_int_t("b5_2102444444300043220033312343422310201232433102022133030");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Senary or Seximal (base 6)
		b = su::big_int_t("b6_5255412204241411042310553444014330331541545304030");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Septenary or Septimal (base 7)
		b = su::big_int_t("b7_1103504602560214512564065241004163456611625454");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Octal (base 8)
		b = su::big_int_t("b8_1347016464530012776614213160636644257523322");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Nonary or Nonal (base 9)
		b = su::big_int_t("b9_7458041461481501320772481804577230718180");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Decimal (base 10)
		// Yes this makes sense. We also have to make sure that explicitly declaring base 10 works.
		b = su::big_int_t("b10_123456789012345678909876543211234567890");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Undecimal, Unodecimal, or Undenary (base 11)
		b = su::big_int_t("b11_3aa2716a7880a695301782402135a7305476a");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Duodecimal or Dozenal (base 12)
		b = su::big_int_t("b12_210b88ab57786788b71608520b9892195016");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Tredecimal or Tridecimal (base 13)
		b = su::big_int_t("b13_185a8cb4592941c511a06c6b3c548963106");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Quattuordecimal or Quadrodecimal (base 14)
		b = su::big_int_t("b14_1c0530ad373bc16512c9b9439c001d42d4");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Quindecimal or Pentadecimal (base 15)
		b = su::big_int_t("b15_2cdc8b3b93b1c8100a142eb6abcc67d60");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Hexadecimal (base 16)
		b = su::big_int_t("b16_5CE0E9A56015FEC622CE19ED22BEA6D2");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Septendecimal or Heptadecimal (base 17)
		b = su::big_int_t("b17_f129b7a38997dd0a868b5ac4d9d3f95");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Octodecimal (base 18)
		b = su::big_int_t("b18_2cee3e14d46232cc6eaa1214h0922d0");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Undevicesimal or Nonadecimal (base 19)
		b = su::big_int_t("b19_a374b6a63db2hc83d8219af8f6f95a");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Vigesimal (base 20)
		b = su::big_int_t("b20_25jg9i11dabhc25cf6bb393fag0jea");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 21
		b = su::big_int_t("b21_bf7hf2ba267f87bb96f5j2cgdcdfi");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 22
		b = su::big_int_t("b22_343ca1aib9632dljhf95h8i21ffea");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 23
		b = su::big_int_t("b23_l2lj7lg2dhl0hcdjjb60beadfl6f");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Quadravigesimal (base 24)
		b = su::big_int_t("b24_6ggkffn6jankfe1ma2hcfah7830i");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 25
		b = su::big_int_t("b25_25eoon04ha3i7jjcg21dei5ac8ff");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Hexavigesimal (base 26)
		b = su::big_int_t("b26_k1aiiie118m76cn1khkj60i6n06");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Septemvigesimal (base 27)
		b = su::big_int_t("b27_7dq1ae1ejf19inbejo4hg70lh5i");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 28
		b = su::big_int_t("b28_2plb7o15rb1f5kp0jli44afjlki");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 29
		b = su::big_int_t("b29_1505jcj8fef7q9fqs0n68bn52os");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Trigesimal (base 30)
		b = su::big_int_t("b30_eh3lnmsofja5d8htcmlg444m30");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 31
		b = su::big_int_t("b31_6cumn16bf01d7d7i7a5otkriob");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Duotrigesimal (base 32)
		b = su::big_int_t("b32_2ss3kqao0lvr325jgptkhbt9mi");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 33
		b = su::big_int_t("b33_1bch1qg2i8a9m7umg4q27b26vl");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 34
		b = su::big_int_t("b34_ln1tiwhrb95n0t006c46n4p4m");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// base 35
		b = su::big_int_t("b35_asdxq9h1ety28y9rrtliuvnyp");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
		
		/////// Hexatrigesimal (base 36)
		b = su::big_int_t("b36_5hy8cqpp6qj5xsoal3jybtioi");
		
		EXPECT_EQ(a, b);
		EXPECT_EQ(b, a);
		EXPECT_EQ(b.to_string(), a.to_string());
		EXPECT_EQ(b.to_string(), "123456789012345678909876543211234567890");
	}
}
