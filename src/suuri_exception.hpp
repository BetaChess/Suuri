#pragma once

namespace suuri
{

class logic_error : public std::exception
{};

class divide_by_zero : public logic_error
{
public:
	[[nodiscard]] constexpr const char* what() const noexcept override
	{
		return "Cannot do integer division by zero";
	}
};

}
