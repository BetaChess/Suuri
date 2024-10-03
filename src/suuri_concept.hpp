#pragma once

namespace suuri
{
template<typename T>
struct is_big_int : std::false_type{};

template<typename T>
constexpr typename is_big_int<T>::value_type is_big_int_t = is_big_int<T>::value;

}