#pragma once

#include <cstdint>
#include <vector>

namespace suuri
{

typedef uint32_t digit_t;
typedef std::vector<digit_t> digit_storage_t;

constexpr digit_t base = 2147483648;

}