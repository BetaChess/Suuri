#pragma once

#include <big_int.hpp>
#include <fstream>
#include <gtest/gtest.h>

namespace su = suuri;

template<typename T, bool convertToInt = true>
void run_pre_generated_test_file_bin_op(std::string fileName, su::big_int_t (*binOp)(const su::big_int_t& l, const su::big_int_t& r))
{
	std::fstream file;
	file.open(fileName, std::ios::in);

	ASSERT_TRUE(file.is_open()) << "Unable to open test file " << fileName;

	std::string input;
	T left, right;
	std::string expected;

	size_t line_counter = 0;
	while (file >> input)
	{
		line_counter++;
		if constexpr (convertToInt)
			left = static_cast<T>(std::stoll(input));
		else
			left = input;
		file >> input;
		if constexpr (convertToInt)
			right = static_cast<T>(std::stoll(input));
		else
			right = input;
		file >> expected;

		EXPECT_EQ(binOp(su::big_int_t{left}, su::big_int_t{right}), su::big_int_t{expected})
				<< "Failed at line " << line_counter;
	}

	file.close();
}