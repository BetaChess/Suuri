#pragma once

#include "suuri_core.hpp"


namespace suuri
{

class BigInt
{
public:
	//// Constructors
	constexpr BigInt()
	{}
	
	//// Operators
	
	/// Comparison Operators
	
	constexpr bool operator==(const BigInt& other) const
	{
		return false;
	}
	
	constexpr bool operator<(const BigInt& other) const
	{
		return false;
	}
	
	constexpr bool operator<=(const BigInt& other) const
	{
		return false;
	}
	
	constexpr bool operator>(const BigInt& other) const
	{
		return false;
	}
	
	constexpr bool operator>=(const BigInt& other) const
	{
		return false;
	}
	
	constexpr std::strong_ordering operator<=>(const BigInt& other) const
	{
		return std::strong_ordering::less;
	}
	
	/// Arithmetic Operators
	
	
	
	
private:

};

}