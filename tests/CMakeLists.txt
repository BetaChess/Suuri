
project ("library_tests")

add_executable(${PROJECT_NAME} "conversion-tests.cpp" "logic-operator-tests.cpp" "basic-arithmatic-tests.cpp")

target_include_directories(${PROJECT_NAME} 
	PUBLIC ../src/
    PUBLIC ../../vendor/googletest/googletest/include
)

target_link_directories(${PROJECT_NAME}
	PRIVATE ../src/
	PRIVATE ../../vendor/googletest/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest_main
	suuri
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