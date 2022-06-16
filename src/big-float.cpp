
#include "big-float.h"

namespace suuri
{

// Specializations for base 16 methods (only int8_t, as no more space is needed)
//template<>
//std::string BigFloat<int8_t, 16>::str_hex() const noexcept
//{
//	std::stringstream ss;
//	if (negative_)
//		ss << '-';
//
//	// Put the digits in reverse order (most significant to least significant)
//	auto it = digits_.end();
//	while (it != digits_.begin())
//	{
//		it--;
//
//		if (*it < 10)
//			ss << static_cast<char>(*it + '0');
//		else
//			ss << static_cast<char>(*it + 'A' - 10);
//	}
//
//	return ss.str();
//};

// Specializations for base 10 methods (only int8_t, as no more space is needed)
template<>
std::string BigFloat<int8_t, 10>::str() const noexcept
{
	std::stringstream ss;
	if (negative_)
		ss << '-';

	if (decimal_position_ == 0)
	{
		auto it = digits_.end();
		while (it != digits_.begin())
		{
			it--;
			ss << static_cast<char>(*it + '0');
		}
	}
	else if (decimal_position_ < digits_.size())
	{
		// Put the digits in reverse order (most significant to least significant). 
		// Print the digits before the decimal point.
		auto it = digits_.end();
		while (it != (digits_.begin() + decimal_position_))
		{
			it--;
			ss << static_cast<char>(*it + '0');
		}
		ss << '.';

		// Print the digits after the decimal point.
		while (it != digits_.begin())
		{
			it--;
			ss << static_cast<char>(*it + '0');
		}
	}
	else
	{
		ss << '0' << '.';
		for (size_t i = 0; i < decimal_position_ - digits_.size(); i++)
			ss << '0';
		
		auto it = digits_.end();
		while (it != digits_.begin())
		{
			it--;
			ss << static_cast<char>(*it + '0');
		}
	}

	return ss.str();
};

// Specializations for base 2 methods (only int8_t, as no more space is needed)
//template<>
//std::string BigFloat<int8_t, 2>::str_bin() const noexcept
//{
//	std::stringstream ss;
//	if (negative_)
//		ss << '-';
//
//	// Put the digits in reverse order (most significant to least significant)
//	auto it = digits_.end();
//	while (it != digits_.begin())
//	{
//		it--;
//		ss << static_cast<char>(*it + '0');
//	}
//
//	return ss.str();
//};

}