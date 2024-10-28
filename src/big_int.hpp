#pragma once

#include "suuri_core.hpp"
#include "suuri_exception.hpp"
#include "suuri_concept.hpp"

#include <algorithm>
#include <assert.h>
#include <concepts>
#include <iostream>
#include <ostream>
#include <string>

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
		
		while (num >= base)
		{
			digits_.push_back(num % base);
			num /= base;
		}
		digits_.push_back(num);
	}
	/**
	 * @param digits An	 rvalue reference to a digit_storage_t container holding the digits of the integer.
	 * @param negative Flag indicating if the integer is negative. Defaults to false.
	 */
	constexpr explicit BigInt(digit_storage_t &&digits, bool negative = false)
		: digits_(std::move(digits)), negative_(negative)
	{}
	/**
	 * @param digits A reference to a digit_storage_t container holding the digits of the integer.
	 * @param negative Flag indicating if the integer is negative. Defaults to false.
	 */
	constexpr explicit BigInt(const digit_storage_t &digits, bool negative = false)
		: digits_(digits.begin(), digits.end()), negative_(negative)
	{}
	/**
	 * Initialise using a string view
	 * @param str A string view containing the digits of the integer (see spec for how to specify a base other than 10).
	 */
	constexpr explicit BigInt(const std::string& str)
		: digits_({0}), negative_(false)
	{
		uint32_t b;
		
		size_t i = 0;
		if (str[i] == 'b')
		{
			i++;
			if (str[i] < '0' || str[i] > '9')
				throw std::invalid_argument("Invalid base argument!");
			if (str[i + 1] == '_')
			{
				b = std::stoi(str.substr(i, i + 1));
				i++;
			}
			else
			{
				b = std::stoi(str.substr(i, i + 2));
				i += 2;
			}
			if (str[i] != '_' || b > 36)
				throw std::invalid_argument("Invalid base argument!");
			i++;
		}
		else
			b = 10;
		
		bool negative;
		if (str[i] == '-')
		{
			negative = true;
			i++;
		}
		else
			negative = false;
		
		*this += BigInt(convert_char_to_int(str[i], b));
		i++;
		for (; i < str.size(); i++)
		{
			*this *= BigInt(b);
			*this += BigInt(convert_char_to_int(str[i], b));
		}
		
		negative_ = negative;
	}
	
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
		if (is_zero() && rhs.is_zero())
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
		if (is_zero() && rhs.is_zero())
			return false;
		if (negative_ != rhs.negative_)
			return negative_;
		
		auto compareResult = digits_compare(digits_, rhs.digits_);
		
		if (negative_)
			return compareResult == std::strong_ordering::greater;
		
		return compareResult == std::strong_ordering::less;
	}
	constexpr bool operator<=(const BigInt& rhs) const
	{
		if (is_zero() && rhs.is_zero())
			return true;
		if (negative_ != rhs.negative_)
			return negative_;
		
		auto compareResult = digits_compare(digits_, rhs.digits_);
		if (compareResult == std::strong_ordering::equal)
			return true;
		if (negative_)
			return compareResult == std::strong_ordering::greater;
		
		return compareResult == std::strong_ordering::less;
	}
	constexpr bool operator>(const BigInt& rhs) const
	{
		if (is_zero() && rhs.is_zero())
			return false;
		if (negative_ != rhs.negative_)
			return rhs.negative_;
		
		auto compareResult = digits_compare(digits_, rhs.digits_);
		
		if (negative_)
			return compareResult == std::strong_ordering::less;
		
		return compareResult == std::strong_ordering::greater;
	}
	constexpr bool operator>=(const BigInt& rhs) const
	{
		if (is_zero() && rhs.is_zero())
			return true;
		if (negative_ != rhs.negative_)
			return rhs.negative_;
		
		auto compareResult = digits_compare(digits_, rhs.digits_);
		if (compareResult == std::strong_ordering::equal)
			return true;
		if (negative_)
			return compareResult == std::strong_ordering::less;
		
		return compareResult == std::strong_ordering::greater;
	}
	constexpr std::strong_ordering operator<=>(const BigInt& rhs) const
	{
		if (is_zero() && rhs.is_zero())
			return std::strong_ordering::equal;
		if (negative_ != rhs.negative_)
		{
			if (negative_)
				return std::strong_ordering::less;
			return std::strong_ordering::greater;
		}
		
		if (negative_)
			return digits_compare(rhs.digits_, digits_);
		return digits_compare(digits_, rhs.digits_);
	}
	
	/// Arithmetic Operators
	
	// ---------- Addition
	
	constexpr BigInt operator+(const BigInt& rhs) const
	{
		return (BigInt(*this) += rhs);
	}
	constexpr BigInt& operator+=(const BigInt& rhs)
	{
		if (rhs.is_zero())
			return *this;
		
		if (negative_ == rhs.negative_)
		{
			add_digits(rhs);
		}
		else if (digits_compare(digits_, rhs.digits_) == std::strong_ordering::greater)
		{
			subtract_digits(rhs);
		}
		else
		{
			subtract_lhs_from_rhs_digits(rhs);
			negate();
		}

		remove_leading_zeros();
		return *this;
	}
	
	// ---------- Subtraction
	
	constexpr BigInt operator-(const BigInt& rhs) const
	{
		return BigInt(*this) -= rhs;
	}
	constexpr BigInt& operator-=(const BigInt& rhs)
	{
		if (rhs.is_zero())
			return *this;
		
		if (negative_ != rhs.negative_)
		{
			add_digits(rhs);
		}
		else if (digits_compare(digits_, rhs.digits_) == std::strong_ordering::greater)
		{
			subtract_digits(rhs);
		}
		else
		{
			subtract_lhs_from_rhs_digits(rhs);
			negate();
		}

		remove_leading_zeros();
		
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
		return long_multiplication(rhs);
	}
	constexpr BigInt& operator*=(const BigInt& rhs)
	{
		*this = long_multiplication(rhs);
		return *this;
	}
	
	// ---------- Division
	
	constexpr BigInt operator/(const BigInt& rhs) const
	{
		if (rhs.is_zero())
			throw divide_by_zero();
		
		if (rhs.digits_.size() == 1)
			return divide_small(static_cast<int64_t>(rhs.digits_[0]) * (rhs.negative_ * -1 + !rhs.negative_)).first;
		
		return divide_binary_search(rhs);
	}
	constexpr BigInt& operator/=(const BigInt& rhs)
	{
		*this = divide_binary_search(rhs);
		return *this;
	}
	constexpr BigInt operator%(const BigInt& rhs) const
	{
		if (rhs.is_zero())
			throw divide_by_zero();
		
		if (rhs.digits_.size() == 1)
			return divide_small(static_cast<int64_t>(rhs.digits_[0]) * (rhs.negative_ * -1 + !rhs.negative_)).second;
		
		return *this - rhs * (*this / rhs);
	}
	constexpr BigInt& operator%=(const BigInt& rhs)
	{
		*this = *this % rhs;
		
		return *this;
	}
	
	//// Misc methods

	/**
	 * @brief Checks if the value is zero.
	 *
	 * @return True if the value is zero, false otherwise.
	 */
	[[nodiscard]] constexpr bool is_zero() const noexcept
	{
		return digits_.size() == 1 && digits_[0] == static_cast<digit_t>(0);
	}

	//// State mutator methods
	
	/**
	 * @brief Negates the BigInt object.
	 *
	 * @return True if the resulting object is now negative. False otherwise.
	 * @note Always returns false if the object is the zero value.
	 */
	constexpr bool negate() noexcept
	{
		negative_ = !negative_;
		return !is_zero() && negative_;
	};
	
	//// Multiplication methods
	
	[[nodiscard]] constexpr BigInt long_multiplication(const BigInt& rhs) const
	{
		BigInt ret;
		ret.digits_.resize(digits_.size() + rhs.digits_.size());
		
		for (size_t i = 0; i < digits_.size(); i++)
		{
			for (size_t j = 0; j < rhs.digits_.size(); j++)
			{
				uint64_t res = static_cast<uint64_t>(ret.digits_[i + j]) + static_cast<uint64_t>(digits_[i]) * static_cast<uint64_t>(rhs.digits_[j]);
				ret.digits_[i + j + 1] += res / base;
				ret.digits_[i + j] = static_cast<uint32_t>(res % base);
			}
		}

		ret.negative_ = negative_ ^ rhs.negative_;
		if (ret.digits_.back() == 0)
			ret.digits_.pop_back();

		return ret;
	}

	[[nodiscard]] constexpr BigInt karatsuba_multiplication(const BigInt& rhs) const
	{
		if (digits_.size() < long_multiplication_digit_threshold || rhs.digits_.size() < long_multiplication_digit_threshold)
			return long_multiplication(rhs);

		const uint64_t n = digits_.size() > rhs.digits_.size() ? digits_.size() : rhs.digits_.size();
		const uint64_t half = n / 2;
		auto x_1 = *this; // x_0
		x_1.right_shift(half);
		auto x_0 = *this; // x_1
		if (x_0.digits_.size() > half)
			x_0.digits_.resize(digits_.size() - x_1.digits_.size());
		auto y_1 = rhs; // y_0
		y_1.right_shift(half);
		auto y_0 = rhs; // y_1
		if (y_0.digits_.size() > half)
			y_0.digits_.resize(rhs.digits_.size() - y_1.digits_.size());
		
		auto z_0 = x_0.karatsuba_multiplication(y_0);
		auto z_2 = x_1.karatsuba_multiplication(y_1);
		auto x0_x1 = x_1 + x_0;
		auto y0_y1 = y_1 + y_0;
		auto z_1 = x0_x1.karatsuba_multiplication(y0_y1) - z_2 - z_0;

		z_2.left_shift(2*half);
		z_1.left_shift(half);

		return z_0 + z_1 + z_2;
	}
	
	//// Division methods
	
	[[nodiscard]] constexpr std::pair<BigInt, BigInt> divide_small(int64_t rhs) const
	{
		uint64_t remainder = 0;
		digit_storage_t digits;
		bool result_negative = negative_ != (rhs < 0);
		rhs = rhs < 0 ? -rhs : rhs;

		for (size_t i = digits_.size() - 1; i < static_cast<size_t>(-1); i--)
		{
			digit_t next = (digits_[i] + remainder * base) / rhs;
			remainder = (digits_[i] + remainder * base) % rhs;
			digits.push_back(next);
		}

		std::ranges::reverse(digits);
		
		auto quotient = BigInt{std::move(digits)};
		quotient.remove_leading_zeros();
		quotient.negative_ = result_negative;
		auto ret_remainder = BigInt{remainder};
		ret_remainder.negative_ = negative_;
		
		return {quotient, ret_remainder};
	}
	
	[[nodiscard]] constexpr BigInt divide_binary_search(const BigInt& rhs) const
	{
		BigInt low{0};
		BigInt mid;
		BigInt high{*this};
		high.negative_ = false;
		
		BigInt quotient{0};
		while (low <= high)
		{
			mid = low + (high - low).divide_small(2).first;
			
			if (digits_compare((mid * rhs).digits_, digits_) == std::strong_ordering::greater)
			{
				high = mid - 1;
			}
			else
			{
				quotient = mid;
				low = mid + 1;
			}
		}
		
		quotient.negative_ = negative_ != rhs.negative_;
		
		return quotient;
	}
	
	//// State accessor methods
	// None so far
	
	//// Conversion methods

	// TODO: Convert to different base string
	[[nodiscard]] constexpr std::string to_string() const
	{
		// TODO: This is slow ish, but definitely usable for most things. Make it faster.
		std::vector<char> digits;
		
		BigInt num = *this;
		num.negative_ = false;
		
		while (num >= 10)
		{
			auto division_result = num.divide_small(10);
			num = division_result.first;
			auto nextDigit = static_cast<char>(division_result.second.digits_[0]);
			digits.push_back(nextDigit);
		}
		digits.push_back(static_cast<char>(num.digits_[0]));
		
		std::string ret;
		ret.resize(digits.size());

		for (int i = 0; i < ret.size(); i++)
		{
			ret[ret.size() - i - 1] = static_cast<char>('0' + digits[i]);
		}

		return ret;
	}

	//// Math operations

	[[nodiscard]] constexpr int8_t sgn() const noexcept
	{
		if (is_zero())
			return 0;

		return negative_ ? -1 : 1;
	}

	[[nodiscard]] constexpr BigInt abs() const noexcept
	{
		BigInt ret = *this;
		ret.negative_ = false;
		return ret;
	}

	[[nodiscard]] constexpr BigInt pow(uint64_t n) const
	{
#ifndef ZERO_POW_ZERO_IS_ONE
		assert(!(is_zero() && n == 0) && "0 to the power of 0 is undefined");
#endif
		if (n == 0)
			return 1;

		auto x = *this;
		decltype(x) y = 1;
		while (n > 1)
		{
			if (n % 2)
			{
				y = x * y;
				n--;
			}
			x *= x;
			n /= 2;
		}
		return x * y;
	}

private:
	digit_storage_t digits_;
	bool negative_;

	//// Static constexpr member variables

	static constexpr size_t long_multiplication_digit_threshold = 3;
	
	//// Private methods
	
	/// Helper methods

	constexpr bool remove_leading_zeros()
	{

		if (digits_.size() == 1)
			return false;

		auto it = digits_.rbegin();
		while (it != digits_.rend() && *it == 0)
			++it;

		if (it == digits_.rend())
		{
			digits_.resize(1);
			digits_[0] = 0;
			return true;
		}

		auto toKeep = std::distance(it, digits_.rend());
		// TODO: Maybe switch this to resize(max(toKeep, 1)) and remove the previous if statement?
		digits_.resize(toKeep);

		return true;
	}
	
	/// Addition methods
	
	constexpr BigInt& add_digits(const BigInt& rhs)
	{
		// We're going to need at least as much storage for the digits as rhs.
		// TODO: Add optimisation that checks if we need rhs.size() + 1
		if (rhs.digits_.size() > digits_.size())
		{
			digits_.resize(rhs.digits_.size());
		}

		// Add the digits
		digit_t carry = 0;
		for (size_t i = 0; i < rhs.digits_.size(); i++)
		{
			digit_t sum = digits_[i] + rhs.digits_[i] + carry;

			bool overflow = sum >= suuri::base;
			digits_[i] = static_cast<uint32_t>(sum - suuri::base * overflow);
			carry = overflow;

			// TODO: Benchmark
			//digits_[i] = sum % suuri::base;
			//carry = sum / suuri::base;
		}
		
		if (carry)
		{
			// This has to be done before in case rhs is lhs
			auto n = rhs.digits_.size();
		
			digits_.resize(digits_.size() + 1);
		
			while (digits_[n] == suuri::base - 1)
			{
				digits_[n] = 0;
				n++;
			}
			
			digits_[n]++;
		}
		
		return *this;
	}

	constexpr BigInt& subtract_digits(const BigInt& rhs)
	{
		int64_t carry = 0;
		size_t i = 0;
		for (; i < rhs.digits_.size(); i++)
		{
			int64_t diff = static_cast<int64_t>(digits_[i]) - static_cast<int64_t>(rhs.digits_[i]) - carry;

			bool underflow = diff < 0;
			digits_[i] = static_cast<uint32_t>(diff + suuri::base * underflow);
			carry = underflow;
		}
		
		while (carry)
		{
			int64_t diff = static_cast<int64_t>(digits_[i]) - carry;

			bool underflow = diff < 0;
			digits_[i] = static_cast<uint32_t>(diff + suuri::base * underflow);
			carry = underflow;
			
			i++;
		}
		
		if (digits_[digits_.size() - 1] == 0)
			digits_.pop_back();
		
		return *this;
	}
	
	constexpr BigInt& subtract_lhs_from_rhs_digits(const BigInt& rhs)
	{
		//assert(!digitsLessThanFullPrecision(rhs, digits_) && "Subtraction result would be negative, and does thus not works with this function.");
		
		if (rhs.digits_.size() > digits_.size())
		{
			digits_.resize(rhs.digits_.size());
		}

		int64_t carry = 0;
		size_t i = 0;
		for (; i < rhs.digits_.size(); i++)
		{
			int64_t diff = static_cast<int64_t>(rhs.digits_[i]) - static_cast<int64_t>(digits_[i]) - carry;

			bool underflow = diff < 0;
			digits_[i] = static_cast<uint32_t>(diff + suuri::base * underflow);
			carry = underflow;
		}

		while (carry)
		{
			int64_t diff = static_cast<int64_t>(rhs.digits_[i]) - carry;

			bool underflow = diff < 0;
			digits_[i] = static_cast<uint32_t>(diff + suuri::base * underflow);
			carry = underflow;

			i++;
		}
		
		if (digits_[digits_.size() - 1] == 0)
			digits_.pop_back();
		
		return *this;
	}

	/// Shift methods

	constexpr BigInt& left_shift(uint64_t shift_by)
	{
		auto copy = digits_;
		digits_.clear();
		digits_.resize(shift_by + copy.size());

		for (size_t i = 0; i < copy.size(); i++)
		{
			digits_[i + shift_by] = copy[i];
		}

		return *this;
	}

	constexpr BigInt& right_shift(uint64_t shift_by)
	{
		if (shift_by >= digits_.size())
		{
			digits_ = {0};
			return *this;
		}

		digits_.erase(digits_.begin(), digits_.begin() + shift_by);

		return *this;
	}

	// Provide a friend overload for the testing framework.
	friend inline void PrintTo(const BigInt& bigint, std::ostream* os) {
		*os << (bigint.negative_ ? "-[" : "[");
		
		// Print the digits in order
		*os << bigint.digits_[0];
		for (size_t i = 1; i < bigint.digits_.size(); i++)
			*os << ", " << bigint.digits_[i];
		
		*os << "]";
	}
};

typedef BigInt big_int_t;

template<>
struct is_big_int<BigInt> : std::true_type {};

}
