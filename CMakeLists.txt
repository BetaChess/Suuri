cmake_minimum_required(VERSION 3.20)

project("suuri")

enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


# add subdirectories
add_subdirectory("vendor/googletest")
add_subdirectory("src")
add_subdirectory("sandbox")
add_subdirectory("tests")
