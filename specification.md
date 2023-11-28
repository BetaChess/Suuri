# Introduction

The aim of the library is to enable the use of arbitrary precision arithmetic in C++, in a way that is both easy to use, but also offers good performance. 
The focus is on making the library as seamless and easy to use as possible. the goal is to enable usage without reading through thousands of pages of documentation, but rather, to simply implement what is already present for fixed precision arithmetic numbers present in the language.

Thus, when you would use, for example, ``std::sin`` to compute the sine of a ``float`` in standard C++, you would simply use ``suuri::sin`` to compute the sine of a ``suuri::big_float_t`` in Suuri.


# Contents

1. [Introduction](#introduction)
2. [Declaration](#declaration)
    - [Types](#types)
	- [Initialisation](#initialisation)
    - [Advanced Types](#advanced-types)
3. [Basic usage](#basic-usage)
    - [Basic Arithmetic](#basic-arithmetic)
    - [Comparison](#comparison)
    	- [Equality Modes](#equality-modes)
	- [Functions](#functions)
	- [Conversion](#conversion)

# Declaration

Declaring variables in Suuri follows the already existing convention with typedefs (*uint8_t as an example*). Any complexity of the language, such as usage of templates, can be ignored for basic usages of the library.
Though they will still be present for any users who wish to make use of the optional complexity.

## Types

Suuri typedefs the following types for easy usage (all within the suuri namespace, of course):

- ``big_int_t``: Arbitrary precision integer
- ``big_uint_t``: Arbitrary precision unsigned integer (throws an exception if value is decreased below 0)
- ``big_float_t``: Arbitrary presision floating point number

For all types in Suuri, the digits are stored in dynamically allocated memory. The base of these digits is available as a ``constexpr`` global called ``suuri::base`` located in the ``suuri-core.h`` header, which is included in every Suuri library header.

## Initialisation

### Default

Default initialisation is the most basic and will always simply initialise the variable to positive ``0``.

#### Example

```cpp
suuri::big_int_t a;

std::cout << a << std::endl; // prints 0
```

### Initialisation with a builtin primitive

Suuri offers initialisation with any builtin primitive types. For signed small integer types like ``short`` or ``char``, these will simply be statically cast to a signed 64 bit integer (``int64_t``) for intialisation, and the sign of the number will be carried to the initialized object. Likewise with their unsigned counterparts, except these will be cast to (``uint64_t``).

For floating point numbers being assigned to arbitrary arithmetic integer types, the value will simply be rounded down.

For assigning floating point numbers to arbitrary precision floating point types, keep in mind that the IEEE does **NOT** support all base 10 values. For example, assigning a normal ``float`` with the value ``0.152f`` will actually give the value ``0.151999995f``. Thus, if using this type of initialisation, keep in mind that you might get weird approximation behavior on assignment. This is also the case for Suuri floats. Not all base 10 values can be represented with a Suuri float. <br/>

#### Examples

```cpp
suuri::big_int_t a = 5;
suuri::big_int_t b = 5ULL;
suuri::big_int_t c{5ULL};

int normalInt = 123;
suuri::big_int_t d = normalInt;
...
suuri::big_float_t e = 0.152f;
suuri::big_float_t f = 0.152;
suuri::big_float_t g{0.152};

std::cout << e /* or f or g */ << std::endl; // Will NOT necessarily print 0.152 exactly
```

### Initialisation with a string

Suuri offers initialisation with a string (specifically a ``std::string_view``). 
This string can be in any base from 2 to 36 (*base 36 using 0-9 in addition to the letters a-z*). 
The base is specified by the prefix of the string. The prefix is specified by the letter ``b`` followed by the base number, 
followed by ``_`` and then the number itself. This is also where the negative sign goes, if present. If no prefix is specified, the base is assumed to be 10. <br/>
In addition to this, Suuri also adds the option to make literals of the basic types using ``""_BI``, ``""_BUI`` and ``""_BF``.
#### Examples

```cpp
suuri::big_int_t a = suuri::big_int_t("123"); // Base 10 (Decimal)
suuri::big_int_t b = suuri::big_int_t("b2_101010"); // Binary
suuri::big_int_t c = suuri::big_int_t("b16_1a2b3c"); // Hexadecimal
suuri::big_int_t d = suuri::big_int_t("b36_-1a2zqc"); // Base 36 (negative)
// Of course, the real power comes from being able to assign numbers greater than the limits of builtin primitives.
suuri::big_int_t e = suuri::big_int_t("12345678901234567890123456789012345678901234567890123456789012345678901234567890");

// And these all work for floating point as well
suuri::big_float_t f = suuri::big_int_t("123.456");
suuri::big_float_t g = suuri::big_int_t("b2_101010.101010"); // Binary
suuri::big_float_t h = suuri::big_int_t("b16_1a2b3c.1a2b3c"); // Hexadecimal
suuri::big_float_t i = suuri::big_int_t("b36_1a2zqc.1a2zqc"); // Base 36

// Postfix (recommended usage)
auto j = "123"_BI; // Has type suuri::big_int_t
auto k = "123"_BUI; // Has type suuri::big_uint_t
auto l = "123.123"_BF; // Has type suuri::big_float_t
```

### Initialisation with ranges (advanced usage)

Suuri allows you to initialise with any object that fulfills the requirements of a ``std::ranges::range`` concept in addition to the contents of the container being implicitely convertible to ``uint32_t``. See documentation or read the code of the concept ``range_of_integral`` for more information. 
This allows you to initialise a ``suuri::big_int_t`` with a ``vector<int>`` for example. It should, however, be kept in mind that no check will be made on the digits provided. As such, providing negative numbers or numbers that are greater than ``suuri::base`` will result in unexpected behavior.

# Basic usage

Suuri is built to make usage as similar to the builtin primitives as possible,
thus any addition, multiplication or similar will function as expected.
This section will thus mostly focus on which guarantees the spec gives, when doing computations. 

## Precision

Global state is used to control the precision of floating point operations. To set the precision use .... //TODO

## Comparison

For *less than* and *greater than*, comparison works exactly as expected. For equality comparison different modes of operation may be used. 
These must be set at compile time with advanced types (see the documentation for more information), but the builtin typedef `bigfloat_t`. In either case, the left hand side, ``lhs``, of the comparison always determines the mode of comparison.

For three-way comparison (``<=>`` *since C++20*), equality modes still apply, and equality is the first thing checked. In addition, the threeway comparison returns a ``std::strong_ordering`` object. If the mode is set to ``suuri::compare_modes::EXACT`` at compile time, then equivalence will yield ``std::strong_ordering::equal``. 
In other equality modes, or in the case of dynamic equality mode, equality will yield ``std::strong_ordering::equivalent``.

### Equality Modes

#### Exact

Exact equality is exactly what you would expect. It simply checks if all the digits, *whithin the precision range*, are equal. Keep in mind that it will do this up to the precision of ``lhs``. If the precision of ``lhs`` is greater than the precision of ``rhs``, equality comparison will not always give a false result though.
For example, if ``lhs`` has all zeros after the precision of ``rhs`` has ended, then the numbers will still be considered equal.

## Functions

Because of the number of mathematical functions the library plans to support, only a subset will be mentioned here, those being the most common ones.
For any other functions, refer to the reference for specifics on how computations are done, and which guarantees are made.

