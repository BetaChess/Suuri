#include <big_int.hpp>
#include <suuri_concept.hpp>
#include <suuri_math.hpp>

#include <iostream>
#include <chrono>

int main()
{
	// // Add start chrono timer
	// auto start = std::chrono::high_resolution_clock::now();
	//
	// auto base = suuri::big_int_t{2};
	// auto p = suuri::pow(base, 136279841);
	// p -= 1;
	//
	// // End timer
	// auto end = std::chrono::high_resolution_clock::now();
	// // Calculate duration
	// std::chrono::duration<double> elapsed = end - start;
	//
	// // std::cout << s;
	// std::cout << '\n' << elapsed.count() << "s\n";
	// std::cout << suuri::is_big_int_v<suuri::big_int_t>;


	suuri::big_int_t a = suuri::big_int_t("5750445218329239395");
	suuri::big_int_t b = suuri::big_int_t("5833138404614241945");
	suuri::big_int_t expected = suuri::big_int_t("33543142846666615686606727236355423275");

	std::cout << '\n' << (a.karatsuba_multiplication(b)).to_string();

	return 0;
}
