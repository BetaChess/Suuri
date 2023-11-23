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
	{
		num = negative_ ? -num : num;
		
		while (num > base)
		{
			digits_.push_back(num % base);
			num /= base;
		}
		digits_.push_back(num);
	}
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
		: digits_({0}), negative_(false)
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
		if (digits_.size() != rhs.digits_.size())
			return false;
		if (isZero() && rhs.isZero())
			return true;
		if (negative_ != rhs.negative_)
			return false;
		
		// Check if each individual digit is the same
		for (size_t i = 0; i < digits_.size(); i++)
			if (digits_[i] != rhs.digits_[i])
				return false;
		
		return true;
	}
	constexpr bool operator<(const BigInt& rhs) const
	{
		if (isZero() && rhs.isZero())
			return false;
		if (negative_ != rhs.negative_)
			return negative_;
		
		auto compareResult = digitsCompare(digits_, rhs.digits_);
		
		if (negative_)
			return compareResult == std::strong_ordering::greater;
		
		return compareResult == std::strong_ordering::less;
	}
	constexpr bool operator<=(const BigInt& rhs) const
	{
		if (isZero() && rhs.isZero())
			return true;
		if (negative_ != rhs.negative_)
			return negative_;
		
		auto compareResult = digitsCompare(digits_, rhs.digits_);
		if (compareResult == std::strong_ordering::equal)
			return true;
		if (negative_)
			return compareResult == std::strong_ordering::greater;
		
		return compareResult == std::strong_ordering::less;
	}
	constexpr bool operator>(const BigInt& rhs) const
	{
		if (isZero() && rhs.isZero())
			return false;
		if (negative_ != rhs.negative_)
			return rhs.negative_;
		
		auto compareResult = digitsCompare(digits_, rhs.digits_);
		
		if (negative_)
			return compareResult == std::strong_ordering::less;
		
		return compareResult == std::strong_ordering::greater;
	}
	constexpr bool operator>=(const BigInt& rhs) const
	{
		if (isZero() && rhs.isZero())
			return true;
		if (negative_ != rhs.negative_)
			return rhs.negative_;
		
		auto compareResult = digitsCompare(digits_, rhs.digits_);
		if (compareResult == std::strong_ordering::equal)
			return true;
		if (negative_)
			return compareResult == std::strong_ordering::less;
		
		return compareResult == std::strong_ordering::greater;
	}
	constexpr std::strong_ordering operator<=>(const BigInt& rhs) const
	{
		if (isZero() && rhs.isZero())
			return std::strong_ordering::equal;
		if (negative_ != rhs.negative_)
		{
			if (negative_)
				return std::strong_ordering::less;
			return std::strong_ordering::greater;
		}
		
		if (negative_)
			return digitsCompare(rhs.digits_, digits_);
		return digitsCompare(digits_, rhs.digits_);
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


	/**
	 * @brief Checks if the value is zero.
	 *
	 * @return True if the value is zero, false otherwise.
	 */
	[[nodiscard]] constexpr bool isZero() const noexcept
	{
		return digits_.size() == 1 && digits_[0] == static_cast<digit_t>(0);
	}

	/**
	 * @brief Negates the BigInt object.
	 *
	 * @return True if the resulting object is now negative. False otherwise.
	 * @note Always returns false if the object is the zero value.
	 */
	constexpr bool negate() noexcept
	{
		negative_ = !negative_;
		return !isZero() && negative_;
	};
	
	
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