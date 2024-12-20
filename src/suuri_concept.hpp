#pragma once

#include <type_traits>

namespace suuri
{
template<typename T>
struct is_big_int : std::false_type {
};

template<typename T>
constexpr typename is_big_int<T>::value_type is_big_int_v = is_big_int<T>::value;

}// namespace suuri