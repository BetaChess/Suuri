#pragma once

#include "suuri_concept.hpp"

#include <concepts>

namespace suuri
{

///// sgn

template<typename T>
  requires is_big_int_v<T>
constexpr int8_t sgn(const T& n) noexcept
{
  return n.sgn();
};

template<typename T>
  requires std::is_integral_v<T> && std::is_signed_v<T> && (!is_big_int_v<T>)
constexpr int8_t sgn(T n) noexcept
{
  if (n == 0)
    return 0;

  return n < 0 ? -1 : 1;
}

template<typename T>
  requires std::is_integral_v<T> && std::is_unsigned_v<T> && (!is_big_int_v<T>)
constexpr int8_t sgn(T n) noexcept
{
  return n > 0 ? 1 : 0;
}

///// abs

template<typename T>
  requires is_big_int_v<T>
constexpr T abs(const T& n) noexcept
{
  return n.abs();
};

template<typename T>
  requires std::is_integral_v<T> && std::is_signed_v<T> && (!is_big_int_v<T>)
constexpr T abs(T n) noexcept
{
  return n < 0 ? -n : n;
}

template<typename T>
  requires std::is_integral_v<T> && std::is_unsigned_v<T> && (!is_big_int_v<T>)
constexpr T abs(T n) noexcept
{
  return n; // Effectively a no-op
}

///// pow

template<typename T>
  requires is_big_int_v<T>
constexpr T pow(const T& x, uint64_t n)
{
  return x.pow(n);
};

template<typename T>
  requires std::is_integral_v<T> && (!is_big_int_v<T>)
constexpr T pow(T x, uint64_t n) noexcept
{
#ifndef ZERO_POW_ZERO_IS_ONE
  assert(!(is_zero() && n == 0) && "0 to the power of 0 is undefined");
#endif
  if (n == 0)
    return 1;

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





}
