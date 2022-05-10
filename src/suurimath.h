#ifndef SUURIMATH_H
#define SUURIMATH_H

#include <type_traits>

namespace suuri
{
	//// ######################################################################
	// POW FUNCTIONS
	namespace integer
	{
		// Credit to https://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/

		// Calculates x to the power of y for integer values x and y
		template<typename T>
		[[nodiscard]] constexpr T pow(T x, T y) noexcept
		{
			if (y == 0) [[unlikely]]
				return 1;

			const T temp = pow<T>(x, y / 2);
			const T tempSqr = temp * temp;
			const bool isEven = y % 2 == 0;

			return isEven * tempSqr + !isEven * x * tempSqr;
		}

		// Calculates 2 to the power of y for and integer value y
		template<typename T>
		[[nodiscard]] constexpr T pow2(T y) noexcept
		{
			return 1 << y;
		}

		// Calculates a base to the power of y for an integer value y and base
		template<typename T, T base>
		[[nodiscard]] constexpr T pow(T y) noexcept
		{
			if (y == 0) [[unlikely]]
				return 1;

			const T temp = pow<T, base>(y / 2);
			const T tempSqr = temp * temp;
			const bool isEven = y % 2 == 0;

			return isEven * tempSqr + !isEven * base * tempSqr;
		}
	}
}



#endif // SUURIMATH_H