#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
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
class BigFloat
{
public:
	// Number of digits to keep after the decimal point. Ignored if "full_precision" is set to true. Is never ignored for division.
	size_t precision = 100;
	bool full_precision = false;

public:
	using DigitType = digitT;
	using this_t = BigFloat<DigitType, baseVal>;

	// Constructors

	constexpr BigFloat() : digits_(0, 0), negative_(false), decimal_position_(0) {}
	constexpr BigFloat(int64_t initialValue, size_t decimal_position = 0) : negative_(initialValue < 0), decimal_position_(decimal_position)
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
	constexpr BigFloat(std::vector<DigitType>&& digits, bool negative = false, size_t decimal_position = 0) :
		digits_{ digits }, negative_(negative), decimal_position_(decimal_position)
	{}
	constexpr BigFloat(const std::vector<DigitType>& digits, bool negative = false, size_t decimal_position = 0) :
		digits_{ digits }, negative_(negative), decimal_position_(decimal_position)
	{}

	// Public methods
	static constexpr DigitType base() noexcept
	{
		return baseVal;
	}

	/// <summary>
	/// Generates a string representation of the BigFloat in base 10.
	/// </summary>
	std::string str() const noexcept
	{
		return cast_bigfloat<int8_t, 10>().str();
	}

	template<typename newDigitT = int8_t, newDigitT newBaseVal = 10>
	constexpr BigFloat<newDigitT, newBaseVal> cast_bigfloat() const noexcept
	{
		BigFloat<newDigitT, newBaseVal> ret;
		/*auto div = *this;
		this_t rem;
		do
		{
			div.divide_assign(newBaseVal, rem);
			rem.fix_remainder();

			ret.digits_push_back(rem.cast_unsafe<newDigitT>());
		} while (!div.is_zero());*/

		return ret;
	}

	template<typename T2>
	constexpr T2 cast_bigfloat() const noexcept
	{
		return cast_bigint<typename T2::DigitType, T2::base()>();
	}

	template<typename T>
	constexpr T cast() const
	{
		// First, check if the number is too big or small to fit into the thing to be cast to.
		if (*this > std::numeric_limits<T>::max())
		{
			throw std::overflow_error("Cannot cast BigFloat to type.");
		}
		else if (*this < std::numeric_limits<T>::min())
		{
			throw std::underflow_error("Cannot cast BigFloat to type.");
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

	// Access methods
	
	constexpr const std::vector<DigitType>& digits() const noexcept
	{
		return digits_;
	}
	/// <summary>
	/// UNSAFE. Grants direct access to the digits vector. DO NOT USE UNLESS YOU KNOW WHAT YOU ARE DOING!
	/// </summary>
	constexpr std::vector<DigitType>& get_digits_reference()
	{
		return digits_;
	}
	constexpr bool is_negative() const noexcept
	{
		return negative_;
	}
	constexpr bool is_zero() const noexcept
	{
		auto it = digits_.begin();
		while (it != digits_.end())
		{
			if (*it != 0)
			{
				return false;
			}

			it++;
		}

		return true;
	}

	/// <summary>
	/// Gets the number of digits in the integer part. (returns 0 if the integer part is 0)
	/// </summary>
	constexpr size_t integer_part_size() const noexcept
	{
		return (digits_.size() - decimal_position_) * !(decimal_position_ >= digits_.size());
	}
	/// <summary>
	/// Gets the number of digits in the fractional part. (includes trailing zeroes)
	/// </summary>
	constexpr size_t fraction_part_size() const noexcept
	{
		return decimal_position_;
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
	
	/// <summary>
	/// Removes trailing zeroes (after the decimal point).
	/// </summary>
	constexpr this_t& remove_trailing_zeroes()
	{
		// If there are none. Return immediately.
		if (*digits_.begin() != 0)
			return *this;

		// If there are some, remove them.
		auto it = digits_.begin();
		while (*it == 0 && it != digits_.end())
		{
			it++;
		}

		decimal_position_ -= digits_.size() - (digits_.end() - it);
		digits_.erase(digits_.begin(), it);
		
		return *this;
	}

	// ADDITION/SUBTRACTION

	/// <summary>
	/// Add the digits of (other) to this. May add a leading 0, if this has fewer or equally many digits as (other). Ignores signs.
	/// </summary>
	constexpr this_t& digits_add(const this_t& rhs) noexcept
	{
		// Declaring constants
		const size_t integer_size = integer_part_size();
		const size_t integer_size_rhs = rhs.integer_part_size();
		
		const size_t fraction_size = fraction_part_size();
		const size_t fraction_size_rhs = rhs.fraction_part_size();

		const bool has_more_fraction_digits = fraction_size > fraction_size_rhs;

		const this_t* const rightmost_num = has_more_fraction_digits ? this : &rhs;
		const this_t* const other_num = has_more_fraction_digits ? &rhs : this;
		const size_t other_fraction_size = has_more_fraction_digits ? fraction_size_rhs : fraction_size;
		
		const size_t max_size_integer_part = std::max(integer_size, integer_size_rhs);
		const size_t max_size_fraction_part = std::max(fraction_size, fraction_size_rhs);
		
		const size_t max_actual_fraction_part = std::max(std::min(fraction_size, digits_.size()), std::min(fraction_size_rhs, rhs.digits_.size()));

		// Actual final size may be 1 larger than this.
		const size_t final_size = max_size_integer_part + max_size_fraction_part;

		// Create the number to return
		this_t ret;

		bool has_integer_part = max_size_integer_part != 0;
		
		// If neither input has an integer part, then the final size is actually just the number of digits in the number with the most fraction digits.
		ret.digits_.resize(has_integer_part ? final_size : max_actual_fraction_part);
		ret.decimal_position_ = max_size_fraction_part;

		// Compute the digits
		// Copy the digits from the rightmost number to the return number.
		memcpy(ret.digits_.data(), rightmost_num->digits_.data(), sizeof(DigitType) * rightmost_num->digits_.size());

		// Add the other number to ret
		size_t i = max_size_fraction_part - other_fraction_size;
		DigitType carry = 0;
		for (size_t j = 0; j < other_num->digits_.size(); j++, i++)
		{
			ret.digits_[i] += other_num->digits_[j] + carry;
			
			bool overflow = ret.digits_[i] >= baseVal;
			ret.digits_[i] -= baseVal * overflow;
			carry = overflow;
		}
		if (carry)
		{
			[&]() {
				// Go through the remaining digits and set any 9s to 0
				for (; i < ret.digits_.size(); i++)
				{
					if (ret.digits_[i] != 9)
					{
						ret.digits_[i] += 1;
						return; // If we meet something that is not a 9, add 1 to it and return out of the lambda.
					}

					ret.digits_[i] = 0;
				}

				// If we reach here, all the remaining digits were 9s, so we need to add a digit.
				ret.digits_.push_back(1);
			}();
		}
		
		*this = std::move(ret);

		return *this;
	}

	/// <summary>
	/// Simply pushes a given digits to the most significant spot.
	/// </summary>
	constexpr this_t& digits_push_back(const DigitType& digit) noexcept
	{
		digits_.push_back(digit);
		return *this;
	}
	
	constexpr this_t& clip_to_n_decimals(size_t n)
	{
		// BUG
		if (decimal_position_ > n)
		{
			if (static_cast<int64_t>(n) <= static_cast<int64_t>(decimal_position_) - static_cast<int64_t>(digits_.size()))
			{
				digits_ = {0};
				decimal_position_ = 0;
			}
			else
			{
				size_t to_erase = decimal_position_ - n;
				digits_.erase(digits_.begin(), digits_.begin() + to_erase);

				decimal_position_ = n;
			}
		}
		return *this;
	}

	/// <summary>
	/// Rounds to n decimal places (DOES NOT ERASE ANY DIGITS, USE 'clip_to_n_decimals' TO ERASE AFTER ROUNDING)
	/// </summary>
	constexpr this_t& round_nth_decimal(size_t n)
	{
		if (decimal_position_ > n)
		{
			if (static_cast<int64_t>(n) <= static_cast<int64_t>(decimal_position_) - static_cast<int64_t>(digits_.size()))
			{
				digits_ = { 0 };
				decimal_position_ = 0;
			}
			else
			{
				size_t i = decimal_position_ - n;
				digits_[i] += static_cast<float>(digits_[i - 1]) >= baseVal / 2.0f;
				bool overflow = digits_[i] >= baseVal;
				digits_[i] -= baseVal * overflow;
				DigitType carry = overflow;
				i++;

				while (i < digits_.size())
				{
					if (!carry)
						break;

					digits_[i] += carry;
					bool overflow = digits_[i] >= baseVal;
					digits_[i] -= baseVal * overflow;
					carry = overflow;
					i++;
				};

				if (carry)
					digits_.push_back(1);
			}
		}

		return *this;
	}

	// OPERATOR OVERLOADS
	// LOGIC OPERATORS
	
	/// <summary>
	/// Checks if the absolute value of this is greater than the absolute value of (other).
	/// </summary>
	constexpr bool is_absolute_greater_than(const this_t& other) const
	{
		const bool less_than_1 = digits_.size() <= decimal_position_;
		const bool other_less_than_1 = other.digits_.size() <= other.decimal_position_;

		if (less_than_1 != other_less_than_1)
			return !less_than_1 && other_less_than_1;

		if (less_than_1)
		{
			auto it_this = digits_.begin();
			auto it_other = other.digits_.begin();

			// Find the first non-zero digit after the decimal point
			for (size_t i = 0; i < decimal_position_; i++)
			{
				if (*it_this != 0)
					break;
				it_this++;
			}
			for (size_t i = 0; i < other.decimal_position_; i++)
			{
				if (*it_other != 0)
					break;
				it_other++;
			}

			auto remaining_digits_this = digits_.end() - it_this;
			auto remaining_digits_other = other.digits_.end() - it_other;

			if (remaining_digits_this > remaining_digits_other)
				return true;
			else if (remaining_digits_other > remaining_digits_this)
				return false;

			// If we are here, they must have equally many significant digits.

			// Start at the most significant digits.
			auto it = digits_.end();
			auto it_o = other.digits_.end();

			for (size_t i = 0; i < remaining_digits_this; i++)
			{
				it--;
				it_o--;

				if (*it > *it_o)
					return true;
				else if (*it == *it_o)
					continue;
				else
					return false;
			}

			return false;
		}
		else
		{
			// Check if the integer size of this is greater than the integer size of (other)
			const size_t integer_size = digits_.size() - decimal_position_;
			const size_t other_integer_size = other.digits_.size() - other.decimal_position_;

			if (integer_size > other_integer_size)
				return true;
			else if (other_integer_size > integer_size)
				return false;

			// Start at the most significant digits.
			auto it = digits_.end();
			auto it_o = other.digits_.end();

			while (it != digits_.begin() && it_o != other.digits_.begin())
			{
				it--;
				it_o--;

				if (*it > *it_o)
					return true;
				else if (*it == *it_o)
					continue;
				else 
					return false;
			}

			while (it_o != other.digits_.begin())
			{
				it_o--;
				if (*it_o != 0)
					return true;
			}

			return false;
		}
	}

	/// <summary>
	/// Checks if the absolute value of this is less than the absolute value of (other).
	/// </summary>
	constexpr bool is_absolute_less_than(const this_t& other) const
	{
		return other.is_absolute_greater_than(*this);
	}
	
	constexpr bool operator==(const this_t& other) const noexcept
	{
		if (is_zero() && other.is_zero())
		{
			return true;
		}
		else if (negative_ != other.negative_)
			return false;
		else if (decimal_position_ - digits_.size() != other.decimal_position_ - other.digits_.size())
			return false;
		

		auto it_this = digits_.begin();
		auto it_other = other.digits_.begin();

		// Find the first non-zero digit after the decimal point
		for (size_t i = 0; i < decimal_position_; i++)
		{
			if (*it_this != 0)
				break;
			it_this++;
		}
		for (size_t i = 0; i < other.decimal_position_; i++)
		{
			if (*it_other != 0)
				break;
			it_other++;
		}
		
		auto remaining_digits_this = digits_.end() - it_this;
		auto remaining_digits_other = other.digits_.end() - it_other;
		
		if (remaining_digits_this != remaining_digits_other)
			return false;
		
		while (it_this != digits_.end())
		{
			if (*it_this != *it_other)
				return false;

			it_this++;
			it_other++;
		}
		
		return true;
	}
	constexpr bool operator!=(const this_t& other) const noexcept
	{
		return !operator==(other);
	}
	constexpr bool operator<(const this_t& other) const
	{
		if (is_zero() && other.is_zero())
			return false;
		else if (negative_ && !other.negative_)
			return true;
		else if (!negative_ && other.negative_)
			return false;

		if (negative_ && other.negative_)
			return is_absolute_greater_than(other);
		else
			return is_absolute_less_than(other);
	}
	constexpr bool operator>(const this_t& other) const
	{
		// If this is greater than (other), then (other) must also necessarily be less than this.
		return other < *this;
	}
	constexpr bool operator<=(const this_t& other) const
	{
		return operator<(other) || operator==(other);
	}
	constexpr bool operator>=(const this_t & other) const
	{
		return operator>(other) || operator==(other);
	}


	// ADDITION/SUBTRACTION

	constexpr this_t& subtract(const this_t& rhs)
	{
		// Declaring constants
		const bool absolute_less_than = is_absolute_less_than(rhs);

		const this_t* const absolute_largest = absolute_less_than ? &rhs : this;
		const this_t* const absolute_smallest = absolute_less_than ? this : &rhs;


		const size_t integer_size = absolute_largest->integer_part_size();
		const size_t integer_size_smallest = absolute_smallest->integer_part_size();

		const size_t fraction_size = absolute_largest->fraction_part_size();
		const size_t fraction_size_smallest = absolute_smallest->fraction_part_size();

		const size_t max_size_integer_part = std::max(integer_size, integer_size_smallest);
		const size_t max_size_fraction_part = std::max(fraction_size, fraction_size_smallest);

		const size_t max_actual_fraction_part = std::max(std::min(fraction_size, absolute_largest->digits_.size()), std::min(fraction_size_smallest, absolute_smallest->digits_.size()));

		// Final size may not actually be exactly this.
		const size_t final_size = max_size_integer_part + max_size_fraction_part;

		// Create the number to return
		this_t ret;

		bool has_integer_part = max_size_integer_part != 0;

		// If neither input has an integer part, then the final size is actually just the number of digits in the number with the most fraction digits.
		ret.digits_.resize((has_integer_part ? final_size : max_actual_fraction_part) + 1);
		ret.decimal_position_ = max_size_fraction_part;

		ret.negative_ = absolute_less_than ^ negative_;

		// Copy the absolute largest into ret
		{
			const size_t offset = max_size_fraction_part - fraction_size;
			memcpy(ret.digits_.data() + offset, absolute_largest->digits_.data(), sizeof(DigitType) * absolute_largest->digits_.size());
		}

		size_t i = max_size_fraction_part - fraction_size_smallest;
		DigitType carry = 0;

		for (size_t j = 0; j < absolute_smallest->digits_.size(); j++, i++)
		{
			ret.digits_[i] -= absolute_smallest->digits_[j] + carry;
			bool subnext = ret.digits_[i] < 0;
			ret.digits_[i] += subnext * baseVal;
			carry = subnext;
		}
		while (carry)
		{
			ret.digits_[i] -= carry;

			bool subNext = (ret.digits_[i] < 0);
			carry = subNext;
			ret.digits_[i] += subNext * baseVal;
			i++;
		}

		*this = std::move(ret);

		return *this;
	}

	constexpr this_t& operator+=(const this_t& other)
	{
		// If the signs are equal
		if (negative_ == other.negative_)
			return digits_add(other);
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
			return digits_add(other);
		else
		{
			return subtract(other).remove_leading_zeroes();
		}
	}
	constexpr this_t operator-(const this_t& other) const
	{
		this_t ret = *this;
		ret -= other;
		return ret;
	}

	// MULTIPLICATION/DIVISION
	
	constexpr this_t& operator/=(const this_t& divisor)
	{
		return newton_raphson_divide(divisor);
	}
	constexpr this_t operator/(const this_t& divisor) const
	{
		this_t ret = *this;
		return ret.newton_raphson_divide(divisor);
	}
	constexpr this_t& operator%=(const this_t& divisor)
	{
		/*this_t rem{};
		divide(divisor, rem);
		rem.fix_remainder();
		*this = rem;*/

		return *this;
	}
	constexpr this_t operator%(const this_t& divisor) const
	{
		/*this_t rem{};
		divide(divisor, rem);
		rem.fix_remainder();*/

		return *this;
	}

	constexpr this_t& operator*=(const this_t& rhs)
	{
		return long_multiply(rhs);
	}
	constexpr this_t operator*(const this_t& rhs) const
	{
		this_t ret = *this;
		ret.long_multiply(rhs);

		return ret;
	}

	// Division methods

	constexpr this_t& newton_raphson_divide(const this_t& divisor)
	{
		if (divisor.is_zero())
			throw std::runtime_error("Error dividing by zero");

		if (divisor == this_t{ {1} })
			return *this;

		// First. Scale an initial value X to be between 0.5 and 1.0
		this_t new_D = divisor;
		new_D.negative_ = false;
		
		// Move the decimal point.
		new_D.decimal_position_ = new_D.digits_.size();
		// Negative means it was shifted right. Positive means it was shifted left.
		const int64_t shifted = static_cast<int64_t>(new_D.decimal_position_) - static_cast<int64_t>(divisor.decimal_position_);
		const uint32_t scaled = new_D.scale_for_division();

		assert(new_D >= this_t(5, 1) && new_D <= this_t(1, 0) && "Scaled value is not between 0.5 and 1.0");

		this_t X = this_t(28235294117647058, 16) - this_t(18823529411764705, 16) * new_D;
		X.full_precision = true;

		size_t S =
			std::max(
			static_cast<size_t>(10),
			static_cast<size_t>(ceil_log2((precision + 1) / floor_log2(17)))
			) + std::max(
			static_cast<int64_t>(integer_part_size()) - static_cast<int64_t>(divisor.integer_part_size()), 
			static_cast<int64_t>(0)
			);

		for (size_t i = 0; i < S; i++)
		{
			X = X * (this_t(2, 0) - new_D * X);
			X.clip_to_n_decimals(2 * precision);
		}

		for (size_t i = 0; i < scaled; i++)
		{
			X *= 2;
		}
		X.decimal_position_ += shifted;

		auto quotient = *this * X;

		quotient.round_nth_decimal(precision + 1);
		quotient.clip_to_n_decimals(precision);

		*this = std::move(quotient);

		return *this;
	}

	// Multiplication methods

	constexpr this_t& long_multiply(const this_t& rhs)
	{
		this_t ret;
		ret.digits_.resize(digits_.size() + rhs.digits_.size());

		for (size_t i = 0; i < digits_.size(); i++)
		{
			for (size_t j = 0; j < rhs.digits_.size(); j++)
			{
				ret.digits_[i + j] += digits_[i] * rhs.digits_[j];
				ret.digits_[i + j + 1] += ret.digits_[i + j] / baseVal;
				ret.digits_[i + j] %= baseVal;
			}
		}

		ret.negative_ = negative_ ^ rhs.negative_;
		ret.decimal_position_ = decimal_position_ + rhs.decimal_position_;

		*this = std::move(ret);
		
		if (digits_.back() == 0)
			digits_.pop_back();

		return *this;
	}

	// Static methods
	
	constexpr this_t get_base_power(uint64_t y)
	{
		this_t ret{ {} };
		ret.digits_.resize(std::min(1ULL, y));
		ret.digits_[y] = 1;
		return ret;
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

	// Stores the decimal offset starting from the least significant digit. 0 meaning that the decimal is after the least significant digit (the number thus just being an integer).
	size_t decimal_position_;

	// Private methods
	
	// Static methods
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
	
	[[nodiscard]] static constexpr uint32_t floor_log2(uint32_t x)
	{
		return x == 1 ? 0 : 1 + floor_log2(x >> 1);
	}

	[[nodiscard]] static constexpr uint32_t ceil_log2(uint32_t x)
	{
		return x == 1 ? 0 : floor_log2(x - 1) + 1;
	}

	// Non-static methods

	/// <summary>
	/// Scales this to be between 0.5 and 1.0 (assuming it is already less than 1.0).
	/// </summary>
	/// <returns>A number 'n' representing the number of times this was multiplied by 2 to scale the value. </returns>
	constexpr uint32_t scale_for_division()
	{
		const uint32_t scale_num = floor_log2(baseVal / digits_[digits_.size() - 1]);
		*this *= 1 << scale_num;

		return scale_num;
	}

	/// <summary>
	/// Moves a specific digit n digits to the end of the vector (towards more significant).
	/// </summary>
	constexpr this_t& digit_move_ms(size_t index, size_t n)
	{
		if (digits_.size() < index + n + 1)
			digits_.resize(index + n + 1);

		digits_[index + n] = digits_[index];
		digits_[index] = 0;

		return *this;
	}
};

// Specializations for base 16 methods (only int8_t, as no more space is needed)

//template<>
//std::string BigFloat<int8_t, 16>::str_hex() const noexcept;

// Specializations for base 10 methods (only int8_t, as no more space is needed)

template<>
std::string BigFloat<int8_t, 10>::str() const noexcept;

// Specializations for base 2 methods (only int8_t, as no more space is needed)

//template<>
//std::string BigFloat<int8_t, 2>::str_bin() const noexcept;


} // namespace suuri ################

#endif // BIGFLOAT_H
