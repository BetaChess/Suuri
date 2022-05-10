#ifndef BIGUINT_H
#define BIGUINT_H

#include <cmath>
#include <vector>
#include <type_traits>
#include <string>

namespace suuri
{	
	template<
		typename digitT,
		digitT baseVal
	>
	class BigInt
	{
	public:
		using DigitType = digitT;

		// Constructors

		BigInt() : digits_(1, 0), negative_(false) {}
		BigInt(DigitType initialValue) : negative_(initialValue < 0)
		{
			DigitType div = initialValue;
			do
			{
				DigitType rem = div % baseVal;
				div /= baseVal;
				
				digits_.push_back(rem);
			} while (div != 0);
		}
		//Initialize with specific digits (least to most significant)
		BigInt(std::vector<DigitType>&& digits, bool negative = false) :
			digits_{digits}, negative_(negative)
		{}

		// Public methods
		inline constexpr DigitType base() const noexcept
		{
			return baseVal;
		}
		
		std::string str() const noexcept
		{
			
			return "";
		}

		template<
			typename newDigitT = int64_t,
			digitT newBaseVal = 10
		>
		constexpr BigInt<newDigitT, newBaseVal> cast_bigint() const noexcept
		{
			
		}
		
		template<typename T>
		constexpr T cast() const
		{
			return 0;
		};

		template<typename T>
		T constexpr cast_unsafe() const noexcept
		{
			T val = 0;
			// Add up the total by using the digits and the base
			
			return val;
		}


		// OPERATOR OVERLOADS
		// LOGIC OPERATORS
		constexpr bool operator==(const BigInt<DigitType, baseVal>& other) const noexcept
		{
			if (digits_.size() != other.digits_.size())
			{
				return false;
			}

			auto itThis = digits_.begin();
			auto itOther = other.digits_.begin();
			while (itThis != digits_.end())
			{
				if (*itThis != *itOther)
				{
					return false;
				}
				++itThis;
				++itOther;
			}

			return true;
		}

		// ADDITION/SUBTRACTION
		BigInt<DigitType, baseVal> operator+(const BigInt<DigitType, baseVal>& other) const
		{
			return BigInt<DigitType, baseVal>(*this) += other;
		}
		BigInt<DigitType, baseVal>& operator+=(const BigInt<DigitType, baseVal>& other)
		{
			if (other.digits_.size() > this->digits_.size())
			{
				this->digits_.resize(other.digits_.size());
			}
			
			DigitType carry = 0;
			for (size_t i = 0; i < other.digits_.size(); i++)
			{
				this->digits_[i] = digits_[i] + other.digits_[i] + carry;
				if (this->digits_[i] >= baseVal)
				{
					this->digits_[i] -= baseVal;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
			}
			if (carry)
				this->digits_.push_back(carry);
			
			return *this;
		}
		BigInt<DigitType, baseVal> operator-(const BigInt<DigitType, baseVal>& other) const
		{
			BigInt<DigitType, baseVal> result;

			// Oh boy
		}

		// MULTIPLICATION/DIVISION
		
		
	private:
		std::vector<DigitType> digits_;
		bool negative_;

	};

	// Specialization for base 10
	/*template<>
	class BigInt<int64_t, 10>
	{
	public:
		using DigitType = int64_t;

		// Constructors
		BigInt(DigitType initialValue) :
			value_{ initialValue }
		{}
		 Initialize with specific digits (least to most significant)
		BigInt(std::vector<DigitType>&& digits)
		{
			value_ = 0;
			for (size_t i = 0; i < digits.size(); i++)
				value_ += digits[i] * pow(10, i);
		}

		// Public methods
		inline constexpr DigitType base() const noexcept
		{
			return 10LL;
		}

		std::string str() const noexcept
		{
			return std::to_string(value_);
		}

		template<typename T>
		constexpr T cast() const
		{
			return static_cast<T>(value_);
		};

		template<typename T>
		T constexpr cast_unsafe() const noexcept
		{
			return static_cast<T>(value_);
		}


	private:
		DigitType value_;
	};*/


	///// TYPEDEFS
	typedef BigInt<uint64_t, 9223372036854775808ULL> BigInt_t;
}

#endif // BIGUINT_H
