#ifndef BIGUINT_H
#define BIGUINT_H

#include <iostream>
#include <cmath>
#include <vector>
#include <type_traits>
#include <string>
#include <cassert>
#include <sstream>
#include <algorithm>

namespace suuri
{

template<
	typename digitT,
	digitT baseVal,
	std::enable_if_t<std::is_integral_v<digitT>>* = nullptr,
	std::enable_if_t<std::is_signed_v<digitT>>* = nullptr
>
class BigInt
{
public:
	using DigitType = digitT;
	using this_t = BigInt<DigitType, baseVal>;

	// Constructors

	constexpr BigInt() : digits_(1, 0), negative_(false) {}
	constexpr BigInt(int64_t initialValue) : negative_(initialValue < 0)
	{
		int64_t div = std::abs(initialValue);
		do
		{
			int64_t rem = div % baseVal;
			div /= baseVal;

			digits_.push_back(static_cast<DigitType>(rem));
		} while (div != 0);
	}
	//Initialize with specific digits (least to most significant)
	constexpr BigInt(std::vector<DigitType>&& digits, bool negative = false) :
		digits_{ digits }, negative_(negative)
	{}

	// Public methods
	static constexpr DigitType base() noexcept
	{
		return baseVal;
	}

	/// <summary>
	/// Generates a string representation of the BigInt in base 10.
	/// </summary>
	std::string str() const noexcept
	{

		return "";
	}

	/// <summary>
	/// Generates a string representation of the BigInt in hexadecimal.
	/// </summary>
	std::string str_hex() const noexcept
	{

		return "";
	}

	/// <summary>
	/// Generates a string representation of the BigInt in binary.
	/// </summary>
	std::string str_bin() const noexcept
	{

		return "";
	}

	template<typename newDigitT = int8_t, digitT newBaseVal = 10>
	constexpr BigInt<newDigitT, newBaseVal> cast_bigint() const noexcept
	{
		return 0;
	}

	template<typename T>
	constexpr T cast() const
	{
		// First, check if the number is too big or small to fit into the thing to be cast to.
		if (*this > std::numeric_limits<T>::max())
		{
			throw std::overflow_error("Cannot cast BigInt to type.");
		}
		else if (*this < std::numeric_limits<T>::min())
		{
			throw std::underflow_error("Cannot cast BigInt to type.");
		}

		return cast_unsafe<T>();
	};

	template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
	constexpr T cast_unsafe() const noexcept
	{
		T val = 0;
		// Add up the total by using the digits and the base
		
		for (size_t i = 0; i < digits_.size(); i++)
		{
			val += static_cast<T>(digits_[i] * this_t::pow(i));
		}

		return val;
	}
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
	constexpr T cast_unsafe() const noexcept
	{
		T val = 0;
		// Add up the total by using the digits and the base

		for (size_t i = 0; i < digits_.size(); i++)
		{
			val += static_cast<T>(digits_[i] * std::pow(baseVal, i));
		}

		return val;
	}
	
	constexpr bool is_negative() const noexcept
	{
		return negative_;
	}
	constexpr bool is_zero() const
	{
		return digits_.size() == 1 && digits_[0] == 0;
	}

	constexpr this_t& negate() noexcept
	{
		negative_ = !negative_;
		return *this;
	}

	// DIGIT MANIPULATION
	// helpers
	
	/// <summary>
	/// Removes leading zeroes (most significant digits).
	/// </summary>
	constexpr this_t& remove_leading_zeroes()
	{
		for (size_t i = digits_.size() - 1; i > 0; i--)
		{
			if (digits_[i] == 0)
				digits_.pop_back();
			else
				return *this;
		}

		return *this;
	}
	
	// logical operations

	/// <summary>
	///  Function to evaluate whether one BigInt is less than another. Assumes there are no leading zeros. (only takes digits into account. Ignores sign).
	/// </summary>
	constexpr bool digits_less_than(const this_t& other) const noexcept
	{
		if (digits_.size() < other.digits_.size())
			return true;
		else if (digits_.size() > other.digits_.size())
			return false;

		for (size_t i = digits_.size() - 1; i > 0; i--)
		{
			if (digits_[i] < other.digits_[i])
				return true;
			else if (digits_[i] == other.digits_[i])
				continue;
			else
				return false;
		}

		return digits_[0] < other.digits_[0];
	}
	/// <summary>
	///  Function to evaluate whether one BigInt is greater than another. Assumes there are no leading zeros. (only takes digits into account. Ignores sign).
	/// </summary>
	constexpr bool digits_greater_than(const this_t& other) const noexcept
	{
		if (digits_.size() > other.digits_.size())
			return true;
		else if (digits_.size() < other.digits_.size())
			return false;

		for (size_t i = digits_.size() - 1; i > 0; i--)
		{
			if (digits_[i] > other.digits_[i])
				return true;
			else if (digits_[i] == other.digits_[i])
				continue;
			else
				return false;
		}

		return digits_[0] > other.digits_[0];
	}
	/// <summary>
	///  Function to evaluate whether one BigInt is equal to another. Assumes there are no leading zeros. (only takes digits into account. Ignores sign).
	/// </summary>
	constexpr bool digits_equal(const this_t& other) const noexcept
	{
		if (digits_.size() < other.digits_.size())
			return false;
		else if (digits_.size() > other.digits_.size())
			return false;

		for (size_t i = digits_.size(); i > 0; i--)
		{
			if (digits_[i - 1] != other.digits_[i - 1])
				return false;
		}

		return true;
	}

	// ADDITION/SUBTRACTION

	/// <summary>
	/// Add the digits of (other) to this. May add a leading 0, if this has fewer or equally many digits as (other). Ignores signs.
	/// </summary>
	constexpr this_t& digits_add(const this_t& other) noexcept
	{
		if (other.digits_.size() > this->digits_.size())
		{
			digits_.resize(other.digits_.size());
		}

		DigitType carry = 0;
		for (size_t i = 0; i < other.digits_.size(); i++)
		{
			digits_[i] = digits_[i] + other.digits_[i] + carry;

			bool overflow = digits_[i] >= baseVal;
			digits_[i] -= baseVal * overflow;
			carry = overflow;
		}

		if (carry)
		{
			digits_.resize(digits_.size() + 1);

			auto n = other.digits_.size();
			while (digits_[n] == 9)
			{
				digits_[n] = 0;
				n++;
			}

			digits_[n] += 1;
		}

		return *this;
	}
	/// <summary>
	/// Subtracts the digits of (other) from this. Does not remove leading zeroes. Digits of other must not be greater than digits of this.
	/// </summary>
	constexpr this_t& digits_subtract(const this_t& other) noexcept
	{
		assert((this->digits_greater_than(other) || this->digits_equal(other)) && "Digits of (other) is greater than the digits of this. ");

		DigitType carry = 0;
		for (size_t i = 0; i < other.digits_.size(); i++)
		{
			digits_[i] = digits_[i] - other.digits_[i] + carry;

			bool underflow = digits_[i] < 0;
			digits_[i] += baseVal * underflow;
			carry = -underflow;
		}

		digits_[digits_.size() - 1] += carry;

		return *this;
	}
	/// <summary>
	/// Manipulates the digits of this to be the absolute difference between this and other. Does not remove leading zeroes.
	/// </summary>
	constexpr this_t& digits_abs_diff(const this_t& other)
	{
		if (other.digits_.size() > this->digits_.size())
		{
			digits_.resize(other.digits_.size());
		}

		for (size_t i = 0; i < other.digits_.size(); i++)
		{
			auto diff = digits_[i] - other.digits_[i];
			digits_[i] = diff < 0 ? -diff : diff;
		}

		return *this;
	}

	
	// OPERATOR OVERLOADS
	// LOGIC OPERATORS
	constexpr bool operator==(const this_t& other) const noexcept
	{
		if (digits_.size() == 1 && digits_[0] == other.digits_[0] && digits_[0] == 0)
		{
			return true;
		}
		else if (negative_ != other.negative_)
			return false;

		return digits_equal(other);
	}
	constexpr bool operator!=(const this_t& other) const noexcept
	{
		return !operator==(other);
	}
	constexpr bool operator<(const this_t& other) const
	{
		if (digits_.size() == 1 && digits_[0] == other.digits_[0] && digits_[0] == 0)
			return false;
		else if (negative_ && !other.negative_)
			return true;
		else if (!negative_ && other.negative_)
			return false;

		if (negative_)
			return digits_greater_than(other);
		else
			return digits_less_than(other);
	}
	constexpr bool operator>(const this_t& other) const
	{
		if (digits_.size() == 1 && digits_[0] == other.digits_[0] && digits_[0] == 0)
			return false;
		else if (negative_ && !other.negative_)
			return false;
		else if (!negative_ && other.negative_)
			return true;

		if (negative_)
			return digits_less_than(other);
		else
			return digits_greater_than(other);
	}

	
	// ADDITION/SUBTRACTION

	constexpr this_t& subtract(const this_t& other)
	{
		int8_t subMult = 1;
		if (digits_less_than(other))
		{
			negate();
			subMult = -1;
		}

		if (other.digits_.size() >= this->digits_.size())
			digits_.resize(other.digits_.size() + 1);

		int8_t carry = 0;
		for (size_t i = 0; i < other.digits_.size(); i++)
		{
			digits_[i] = subMult * digits_[i] - other.digits_[i] * subMult + carry;
			bool subNext = (digits_[i] < 0);
			carry = subNext * -1;
			digits_[i] += subNext * baseVal;
		}

		auto n = other.digits_.size();
		while (carry)
		{
			digits_[n] += carry;

			bool subNext = (digits_[n] < 0);
			carry = subNext * -1;
			digits_[n] += subNext * baseVal;
			n++;
		}

		return *this;
	}

	constexpr this_t& operator+=(const this_t& other)
	{
		// If the signs are equal
		if (negative_ == other.negative_)
			return digits_add(other).remove_leading_zeroes();
		else
		{
			return subtract(other).remove_leading_zeroes();
		}
	}
	constexpr this_t operator+(const this_t& other) const
	{
		this_t ret = *this;
		ret += other;
		return ret;
	}
	constexpr this_t& operator-=(const this_t& other)
	{
		// If the signs are opposite
		if (negative_ ^ other.negative_)
			return digits_add(other).remove_leading_zeroes();
		else
		{
			return subtract(other).remove_leading_zeroes();
			/*if (digits_less_than(other))
				return digits_abs_diff(other).negate().remove_leading_zeroes();
			else
				return digits_subtract(other).remove_leading_zeroes();*/
		}
	}
	constexpr this_t operator-(const this_t& other) const
	{
		this_t ret = *this;
		ret -= other;
		return ret;
	}

	// MULTIPLICATION/DIVISION
	
	/// <summary>
	/// Method used to fix a remainder to be in the correct format. Will simply reverse the digits and remove any leading zeroes.
	/// </summary>
	this_t& fix_remainder()
	{
		std::reverse(digits_.begin(), digits_.end());
		remove_leading_zeroes();

		return *this;
	}

	/// <summary>
	/// Dedicated devide method, in case you want both the quotient and remainder without extra computation. 
	/// </summary>
	/// <param name="remainder_out">: The remainder reference to be written to. IT WILL BE IN REVERSE ORDER AND HAVE LEADING ZEROES. Use "fix_remainder" to fix the remainder to the normal format. </param>
	constexpr this_t divide(const this_t& dividend, this_t& remainder_out) const
	{
		if (dividend.is_zero())
			throw std::runtime_error("Error dividing by zero");

		// If this is less than the dividend (digits, since we don't care about the sign), then this is not divisible by dividend. 
		if (digits_less_than(dividend))
		{
			remainder_out = *this;
			return this_t{ {0} };
		}

		const auto dividendSize = dividend.digits_.size();

		auto compareFunction = [&]() -> bool {
			// Get the relevant part of the remainder (the last digits are the important ones).
			// The remainder will only ever have the same number of digits as the dividend or one more.
			auto remainderCurr = remainder_out.digits_.end() - dividendSize;
			auto dividendCurr = dividend.digits_.end() - 1;

			// If the remainder has an extra digit, it must be larger than the dividend
			if (*(remainderCurr - 1) > 0)
				return true;

			remainderCurr--;

			// Check each digit until the end. If a digit is greater than the corresponding digit of the dividend, then the dividend must be smaller.
			while (1)
			{
				remainderCurr++;

				if (*remainderCurr > *dividendCurr)
					return true;
				else if (*remainderCurr < *dividendCurr)
					return false;

				if (remainderCurr == remainder_out.digits_.end() - 1)
					break;

				dividendCurr--;
			}

			return true;
		};

		{
			auto currentDigit = digits_.crbegin();
			currentDigit += dividend.digits_.size() - 1;

			remainder_out.digits_ = { {0} };
			remainder_out.digits_.insert(remainder_out.digits_.end(), digits_.crbegin(), currentDigit);
		}
		auto currentDigit = digits_.cend()  - dividend.digits_.size() + 1;

		// The quotient will also be reverse order, so we need to reverse it before returning.
		this_t quotient;

		while (currentDigit != digits_.begin())
		{
			currentDigit--;

			remainder_out.digits_.push_back(*currentDigit);
				
			DigitType count = 0; // Counts the number of times the dividend can be subtracted from the current remainder. This will be the next digit.
			while (compareFunction())
			{
				count++;

				auto remIt = remainder_out.digits_.end() - 1; // start at the last digit (least significant digit).
				auto divIt = dividend.digits_.cbegin(); // start at the first digit (least significant digit).

				while (divIt != dividend.digits_.cend())
				{
					*remIt -= *divIt;
					bool carry = (*remIt < 0);
					*remIt += carry * baseVal;
					*(remIt - 1) -= carry;

					remIt--;
					divIt++;
				}
			}

			quotient.digits_.push_back(count);
		}

		std::reverse(quotient.digits_.begin(), quotient.digits_.end());
		quotient.remove_leading_zeroes();

		quotient.negative_ = negative_ ^ dividend.negative_;
		remainder_out.negative_ = quotient.negative_;

		return quotient;
	}
	
	/// <summary>
	/// Dedicated devideAssign method, in case you want both the quotient and remainder without extra computation. 
	/// </summary>
	/// <param name="remainder_out">: The remainder reference to be written to. IT WILL BE IN REVERSE ORDER AND HAVE LEADING ZEROES. Use "fix_remainder" to fix the remainder to the normal format. </param>
	constexpr this_t& divideAssign(const this_t& dividend, this_t& remainder_out)
	{
		*this = divide(dividend, remainder_out);

		return *this;
	}
	
	constexpr this_t& operator/=(const this_t& dividend)
	{
		this_t rem{};
		return divideAssign(dividend, rem);
	}
	constexpr this_t operator/(const this_t& dividend) const
	{
		this_t rem{};
		return divide(dividend, rem);
	}



	// FRIENDS
	friend std::ostream& operator<<(std::ostream& out, const this_t& rhs)
	{
		out << rhs.str();

		return out;
	};

private:
	std::vector<DigitType> digits_;
	bool negative_;

	// Private methods
	[[nodiscard]] static constexpr uint64_t pow(uint64_t y) noexcept
	{
		constexpr uint64_t x = static_cast<uint64_t>(baseVal);

		if (y == 0) [[unlikely]]
			return 1;

		const uint64_t temp = pow(y / 2);
		const uint64_t tempSqr = temp * temp;
		const bool isEven = y % 2 == 0;

		return isEven * tempSqr + !isEven * x * tempSqr;
	}
};

// Specializations for base 16 methods (only int8_t, as no more space is needed)

template<>
std::string BigInt<int8_t, 16>::str_hex() const noexcept;

// Specializations for base 10 methods (only int8_t, as no more space is needed)

template<>
std::string BigInt<int8_t, 10>::str() const noexcept;

// Specializations for base 2 methods (only int8_t, as no more space is needed)

template<>
std::string BigInt<int8_t, 2>::str_bin() const noexcept;


} // namespace suuri ################

#endif // BIGUINT_H
