#include <big_int.hpp>
#include <suuri_concept.hpp>

#include <iostream>
#include <chrono>


suuri::big_int_t fact(uint64_t i){
	suuri::big_int_t res = 1;

	for (int j = 2; j <= i; j++)
	{
//		std::cout << j << '\n';
		res *= j;
	}
	
	return res;
}

suuri::big_int_t fib(uint64_t i)
{
	static std::vector<suuri::big_int_t> mem = {0, 1};

	if (mem.size() > i)
		return mem[i];

	while (mem.size() <= i)
	{
		const suuri::big_int_t f1 = fib(mem.size() - 1);
		const suuri::big_int_t f2 = fib(mem.size() - 2);
		mem.emplace_back(f1 + f2);
	}

	return mem[i];
}


int main()
{
	// Add start chrono timer
	auto start = std::chrono::high_resolution_clock::now();

	auto num = fib(50000);
	auto s = num.to_string();

	// End timer
	auto end = std::chrono::high_resolution_clock::now();
	// Calculate duration
	std::chrono::duration<double> elapsed = end - start;

	std::cout << s;
	std::cout << '\n' << elapsed.count() << "s\n";
	std::cout << suuri::is_big_int_t<suuri::big_int_t>;

	return 0;
}
