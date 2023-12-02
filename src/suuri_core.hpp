#pragma once

#include <cstdint>
#include <vector>
#include <compare>

namespace suuri
{

typedef uint32_t digit_t;
typedef std::vector<digit_t> digit_storage_t;

inline constexpr digit_t base = 2147483648;

static constexpr uint32_t convertCharToInt(char c, uint32_t b = 10)
{
	uint32_t retval;
	
	if (c >= '0' && c <= '9')
		retval = static_cast<uint32_t>(c - '0');
	else if (c >= 'a' && c <= 'z')
		retval = static_cast<uint32_t>(c - 'a' + 10);
	else if (c >= 'A' && c <= 'Z')
		retval = static_cast<uint32_t>(c - 'A' + 10);
	else
		throw std::invalid_argument("Invalid character");

	if (retval >= b)
		throw std::invalid_argument("Invalid character");

	return retval;
}

inline constexpr std::strong_ordering digitsCompare(const digit_storage_t& lhs, const digit_storage_t& rhs) noexcept
{
	if (lhs.size() != rhs.size())
		return lhs.size() < rhs.size() ? std::strong_ordering::less : std::strong_ordering::greater;
	
	// Start from the most significant digit. If any digit is not equal, return digit < otherDigit
	for (size_t i = 0; i < lhs.size(); i++)
		if (lhs[lhs.size() - 1 - i] != rhs[rhs.size() - 1 - i])
			return lhs[lhs.size() - 1 - i] < rhs[rhs.size() - 1 - i] ? std::strong_ordering::less : std::strong_ordering::greater;

	// If we get here, they must be equal
	return std::strong_ordering::equal;
}

}