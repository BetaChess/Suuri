#pragma once

#include "suuri_core.hpp"

#include <concepts>
#include <string_view>


namespace suuri
{

class BigInt
{
public:
	//// Constructors
	
	/**
	 * Initialises to positive 0
	 */
	constexpr BigInt()
		: digits_({0}), negative_(false)
	{}
	/**
	 * Initialises with a primitive integer type
	 * @tparam Must be a builtin primitive integral type
	 */
	template<typename T>
		requires std::is_fundamental_v<T> && std::integral<T>
	constexpr BigInt(T num)
		: digits_(), negative_(num < 0)
	{}
	/**
	 * Initialises the digits directly with a range of positive integers
	 *
	 * @param negative Flag indicating if the integer is negative. Defaults to false.
	 */
	template<std::ranges::range R>
		requires std::integral<std::ranges::range_value_t<R>>
	constexpr explicit BigInt(const R& digits, bool negative = false)
		: digits_(std::ranges::begin(digits), std::ranges::end(digits)), negative_(negative)
	{}
	/**
	 * @param digits An	 rvalue reference to a digit_storage_t container holding the digits of the integer.
	 * @param negative Flag indicating if the integer is negative. Defaults to false.
	 */
	constexpr explicit BigInt(digit_storage_t &&digits, bool negative = false)
		: digits_(std::move(digits)), negative_(negative)
	{}
	/**
	 * Initialise using a string view
	 * @param str A string view containing the digits of the integer (see spec for how to specify a base other than 10).
	 */
	constexpr explicit BigInt(std::string_view str)
		: digits_(), negative_(false)
	{}
	
	// Copy constructor and move constructor
	
	constexpr BigInt(const BigInt& rhs) = default;
	constexpr BigInt(BigInt&& rhs) = default;


	//// Operators
	
	/// Assignment Operators
	
	constexpr BigInt& operator=(const BigInt& rhs) = default;
	constexpr BigInt& operator=(BigInt&& rhs) = default;
	
	/// Comparison Operators
	
	constexpr bool operator==(const BigInt& rhs) const
	{
		return true;
	}
	
	constexpr bool operator<(const BigInt& rhs) const
	{
		return false;
	}
	
	constexpr bool operator<=(const BigInt& rhs) const
	{
		return false;
	}
	
	constexpr bool operator>(const BigInt& rhs) const
	{
		return false;
	}
	
	constexpr bool operator>=(const BigInt& rhs) const
	{
		return false;
	}
	
	constexpr std::strong_ordering operator<=>(const BigInt& rhs) const
	{
		return std::strong_ordering::less;
	}
	
	/// Arithmetic Operators
	
	// ---------- Addition
	
	constexpr BigInt operator+(const BigInt& rhs) const
	{
		return BigInt();
	}
	constexpr BigInt& operator+=(const BigInt& rhs)
	{
		return *this;
	}
	
	// ---------- Subtraction
	
	constexpr BigInt operator-(const BigInt& rhs) const
	{
		return BigInt();
	}
	constexpr BigInt& operator-=(const BigInt& rhs)
	{
		return *this;
	}
	constexpr BigInt operator-()
	{
		auto ret = BigInt(*this);
		ret.negative_ = !negative_;
		return ret;
	}
	
	// ---------- Multiplication
	
	constexpr BigInt operator*(const BigInt& rhs) const
	{
		return BigInt();
	}
	constexpr BigInt& operator*=(const BigInt& rhs)
	{
		return *this;
	}
	
	// ---------- Division
	
	constexpr BigInt operator/(const BigInt& rhs) const
	{
		return BigInt();
	}
	constexpr BigInt& operator/=(const BigInt& rhs)
	{
		return *this;
	}
	constexpr BigInt operator%(const BigInt& rhs) const
	{
		return BigInt();
	}
	constexpr BigInt& operator%=(const BigInt& rhs)
	{
		return *this;
	}
	
	//// Misc methods
	
	[[nodiscard]] constexpr bool isZero() const noexcept
	{
		return digits_.size() == 1 && digits_[0] == static_cast<digit_t>(0);
	}
	
	
private:
	digit_storage_t digits_;
	bool negative_;

	// Provide a friend overload for the testing framework.
	friend void PrintTo(const BigInt& bigint, std::ostream* os) {
		*os << (bigint.negative_ ? "-[" : "[");
		
		// Print the digits in order
		*os << bigint.digits_[0];
		for (size_t i = 1; i < bigint.digits_.size(); i++)
			*os << ", " << bigint.digits_[i];
		
		*os << "]";
	}
};

typedef BigInt big_int_t;

}