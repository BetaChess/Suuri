﻿cmake_minimum_required(VERSION 3.20)

project("suuri_library_tests")

set(SOURCES
	int_tests/comparison.cpp
	int_tests/string.cpp
	int_tests/addition.cpp
	int_tests/subtraction.cpp
	int_tests/multiplication.cpp
	int_tests/division.cpp
	int_tests/suuri_math.cpp
	primitive_tests/suuri_math.cpp
	int_tests/test_helpers.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
						   PUBLIC ../src/
						   PUBLIC ../../vendor/googletest/googletest/include
)

target_link_directories(${PROJECT_NAME}
						PRIVATE ../../vendor/googletest/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
					  gtest_main
)

set_target_properties(${PROJECT_NAME}
					  PROPERTIES
					  CXX_STANDARD 20
					  CXX_STANDARD_REQUIRED YES
					  CXX_EXTENSIONS NO
)

add_test(
		NAME ${PROJECT_NAME}
		COMMAND ${PROJECT_NAME}
)
