#ifndef SUURI_TYPETRAITS_H
#define SUURI_TYPETRAITS_H

#include "big-int.h"
#include "big-float.h"

#include <type_traits>

namespace suuri
{
///// ### INTEGERS

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

}


#endif // SUURI_TYPETRAITS_H
