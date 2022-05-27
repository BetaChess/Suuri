
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
	suuri::BigInt10_t a = 15185;
	suuri::BigInt10_t b = -4;
	suuri::BigInt10_t rem;

	//15185
	//-4

	auto c = a.divide(b, rem);
	rem.fix_remainder();

	std::cout << a << "/" << b.str() << " = " << c.str() << " and the remainder is " << rem.str() << std::endl;

	return 0;
}
