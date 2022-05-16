#ifndef BIGUINT_H
#define BIGUINT_H

#include <iostream>
#include <cmath>
#include <vector>
#include <type_traits>
#include <string>
#include <cassert>

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

	BigInt() : digits_(1, 0), negative_(false) {}
	BigInt(int64_t initialValue) : negative_(initialValue < 0)
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
	BigInt(std::vector<DigitType>&& digits, bool negative = false) :
		digits_{ digits }, negative_(negative)
	{}

	// Public methods
	static inline constexpr DigitType base() noexcept
	{
		return baseVal;
	}

	std::string str() const noexcept
	{

		return "";
	}

	template<typename newDigitT = int64_t, digitT newBaseVal = 10>
	constexpr BigInt<newDigitT, newBaseVal> cast_bigint() const noexcept
	{
		return 0;
	}

	template<typename T>
	constexpr T cast() const
	{
		return 0;
	};

	template<typename T>
	constexpr T cast_unsafe() const noexcept
	{
		T val = 0;
		// Add up the total by using the digits and the base

		return val;
	}

	constexpr bool is_negative() const noexcept
	{
		return negative_;
	}

	constexpr this_t& negate() noexcept
	{
		negative_ = !negative_;
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

	this_t& subtract(const this_t& other)
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
	
	this_t& operator+=(const this_t& other)
	{
		// If the signs are equal
		if (negative_ == other.negative_)
			return digits_add(other).remove_leading_zeroes();
		else
		{
			return subtract(other).remove_leading_zeroes();
		}
	}
	this_t operator+(const this_t& other) const
	{
		this_t ret = *this;
		ret += other;
		return ret;
	}
	this_t& operator-=(const this_t& other)
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
	this_t operator-(const this_t& other) const
	{
		this_t ret = *this;
		ret -= other;
		return ret;
	}
	

	// MULTIPLICATION/DIVISION
	

	// DIGIT MANIPULATION
	// helpers
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
	///  Function to evaluate whether one BigInt is less than another (only takes digits into account. Ignores sign).
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
	///  Function to evaluate whether one BigInt is greater than another (only takes digits into account. Ignores sign).
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
	///  Function to evaluate whether one BigInt is equal to another (only takes digits into account. Ignores sign).
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
	/// Subtracts the digits of (other) from this. Does not remove leading zeroes. (ASSUMES THAT THE DIGITS OF OTHER IS NOT GREATER THAN THE DIGITS OF THIS. USE digits_abs_diff IF THAT IS THE CASE).
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

	// FRIENDS
	//friend std::ostream& operator<<(std::ostream& out, const this_t& rhs);

private:
	std::vector<DigitType> digits_;
	bool negative_;

};

// Specialization for base 10
// TODO: MAKE


///// TYPE TRAIS ### INTEGERS
template<typename T>
struct isBigInt : std::false_type {};

template<typename digitT, digitT baseVal>
struct isBigInt<BigInt<digitT, baseVal>> : std::true_type {};

template<typename T>
inline constexpr bool isBigInt_v = isBigInt<T>::value;

///// INTEGER TYPES END HERE

///// TYPE TRAITS ### SUURI
template<typename T>
struct isBigType : std::false_type {};

template<typename digitT, digitT baseVal>
struct isBigType<BigInt<digitT, baseVal>> : std::true_type {};
// REMEMBER TO ADD OTHER TYPES TO THIS AS THEY ARE ADDDED

template<typename T>
inline constexpr bool isBigType_v = isBigType<T>::value;


} // namespace suuri ################

#endif // BIGUINT_H
