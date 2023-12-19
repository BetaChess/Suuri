#include <big_int.hpp>

#include <iostream>


suuri::big_int_t fact(uint64_t i){
	suuri::big_int_t res = 1;

	for (int j = 2; j <= i; j++)
	{
//		std::cout << j << '\n';
		res *= j;
	}
	
	return res;
}


int main()
{
//	suuri::big_int_t num{"213744164203001278214900687669469982484517189418340686233600000000"};
//	std::cout << (num - 1).to_string();
	
//	suuri::digit_storage_t digits{0, 2075082752, 1478416123, 721428841, 1613066482, 1627084780, 63613171, 2};
//	suuri::big_int_t num{digits};
//	suuri::big_int_t a{"427488328406002556429801375338939964969034378836681372467200000000"};
//	
//	std::cout << (suuri::big_int_t{"427488328406002556429801375338939964969034378836681372467200000000"}/10).to_string();
//	
	auto s = fact(20000).to_string();
	
	std::cout << s;

//	for (int i = 2; i < 500; i++)
//	{
//		if (fact(i).to_string().find(':') != std::string::npos)
//			std::cout << i << '\n';
//	}

	return 0;
}
