#include <big_int.hpp>
#include <suuri_concept.hpp>
#include <suuri_math.hpp>

#include <chrono>
#include <iostream>

int main()
{
	suuri::big_int_t a = suuri::big_int_t("-8382105401607098755");
	suuri::big_int_t b = suuri::big_int_t("6095900384866961812");
	suuri::big_int_t expected = suuri::big_int_t("-51096479543652152805082699968697744060");

	std::cout << '\n'
			  << (a.karatsuba_multiplication(b)).to_string();

	return 0;
}
