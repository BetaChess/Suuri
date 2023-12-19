#include <big_int.hpp>

#include <iostream>


int main()
{
	suuri::big_int_t num{"1234560"};
	
	std::cout << num.to_string();
	
	return 0;
}
