#pragma once

namespace suuri
{

class logic_error : public std::runtime_error
{};

class divide_by_zero : public logic_error
{};

}
