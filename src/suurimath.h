#ifndef SUURIMATH_H
#define SUURIMATH_H

#include "suuri-typetraits.h"

namespace suuri
{

//// ######################################################################
// MISC FUNCTIONS

template<class T, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
constexpr auto abs(T const& x) noexcept
{
	return x < 0 ? -x : x;
}


//// ######################################################################
// POW FUNCTIONS

// Credit to https://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/

// Calculates x to the power of y.
template<
	typename T, 
	std::enable_if_t<!isBigInt_v<T>>* = nullptr,
	std::enable_if_t<std::is_integral_v<T>>* = nullptr,
	std::enable_if_t<std::is_unsigned_v<T>>* = nullptr
>
[[nodiscard]] constexpr T pow(T x, T y) noexcept
{
	if (y == 0) [[unlikely]]
		return 1;

	const T temp = pow<T>(x, y / 2);
	const T tempSqr = temp * temp;
	const bool isEven = y % 2 == 0;

	// Because both (isEven * tempSqr) and (!isEven * x * tempSqr) are computed, this can be very slow for BigInts. 
	// This is, generally, faster for builtin primitives, since calculations can often be done at the same time, and branching is computationally expensive.
	// Therefore, simply including the branch in the arithmetic is faster.
	return isEven * tempSqr + !isEven * x * tempSqr;
}

// Calculates a compile-time known base to the power of y.
template<
	int64_t base,
	typename T = uint64_t,
	std::enable_if_t<!isBigInt_v<T>>* = nullptr,
	std::enable_if_t<std::is_integral_v<T>>* = nullptr,
	std::enable_if_t<std::is_unsigned_v<T>>* = nullptr
>
[[nodiscard]] constexpr T pow(T y) noexcept
{
	constexpr T x = static_cast<T>(base);
	
	if (y == 0) [[unlikely]]
		return 1;

	const T temp = pow<base, T>(y / 2);
	const T tempSqr = temp * temp;
	const bool isEven = y % 2 == 0;

	return isEven * tempSqr + !isEven * x * tempSqr;
}

// Specialization for powers of 2 (with uint64_t and uint32_t)
template<
	typename T = uint64_t,
	std::enable_if_t<!isBigInt_v<T>>* = nullptr,
	std::enable_if_t<std::is_integral_v<T>>* = nullptr,
	std::enable_if_t<std::is_unsigned_v<T>>* = nullptr
>
[[nodiscard]] constexpr T pow2(T y) noexcept
{
	return static_cast<T>(1) << y;
};


////// TYPEDEFS

/// Standard bigint type for doing large calculations.
typedef BigInt<int64_t, static_cast<int64_t>(pow2(31ULL))> BigInt_t;
/// Hexadecimal bigint type.
typedef BigInt<int8_t, 16> BigInt16_t;
/// Decimal (base 10) bigint type.
typedef BigInt<int8_t, 10> BigInt10_t;
/// Binary bigint type.
typedef BigInt<int8_t, 2> BigInt2_t;

} // namespace suuri



#endif // SUURIMATH_H