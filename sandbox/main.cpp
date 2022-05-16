
#include <suurimath.h>

#include <benchmarker.h>

#include <iostream>
#include <random>
#include <vector>
#include <chrono>


int main()
{
	suuri::BigInt_t a = suuri::BigInt_t::base() - 1;
	suuri::BigInt_t b = 1;

	a += b;

	return 0;
}
