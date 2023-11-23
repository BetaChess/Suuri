#pragma once

#include <cstdint>
#include <vector>
#include <compare>

namespace suuri
{

typedef uint32_t digit_t;
typedef std::vector<digit_t> digit_storage_t;

constexpr digit_t base = 2147483648;

constexpr std::strong_ordering digitsCompare(const digit_storage_t& lhs, const digit_storage_t& rhs) noexcept
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