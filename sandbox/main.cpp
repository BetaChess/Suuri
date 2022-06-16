
#include <suurimath.h>

#include <benchmarker.h>

#include <iostream>
#include <random>
#include <vector>
#include <chrono>


int main()
{
	/*suuri::BigInt10_t a = { {6, 3, 1, 0,2,3,1,8,0,2,6,8,9,8,1,5,6,4,5,9,0,8,5,2,0,8,9,4,0,1,3,4,5,5,4,3,7,6,0,9} };
	suuri::BigInt10_t b = 65397;*/
	//suuri::BigInt10_t a = 99999;
	//suuri::BigInt10_t b = 2;
	/*suuri::BigInt10_t a = 8;
	suuri::BigInt10_t b = 7;
	suuri::BigInt10_t rem;*/

	//15185
	//-4

	/*auto c = a.divide(b, rem);
	rem.fix_remainder();*/

	//std::cout << a.newton_raphson_divide(b) << std::endl;

	//std::cout << a << "/" << b.str() << " = " << c.str() << " and the remainder is " << rem.str() << std::endl;

	suuri::BigFloat10_t bf = {15543535, 3};
	bf.round_nth_decimal(2).clip_to_n_decimals(2);

	suuri::BigFloat10_t t1 = { 1243431, 0 };
	suuri::BigFloat10_t t2 = { 4, 2 };
	t2.negate();
	
	t1.newton_raphson_divide(t2);
	t1.remove_trailing_zeroes();
	
	std::cout << t1.str() << std::endl;

	std::cout << (t1 * t2) << std::endl;


	suuri::BigFloat10_t a = 8;
	suuri::BigFloat10_t b = 7;

	std::cout << a.newton_raphson_divide(b) << std::endl;

	
	return 0;
}
