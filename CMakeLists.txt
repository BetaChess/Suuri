
cmake_minimum_required (VERSION 3.8)

project ("Suuri")

enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if (BENCHMARK)
	add_compile_definitions("BENCHMARK_ENABLED")
endif()

add_compile_options("$<$<NOT:$<CONFIG:Debug>>:/Zi>")
add_link_options("$<$<NOT:$<CONFIG:Debug>>:/DEBUG>")
add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:REF>")
add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:ICF>")

# add subdirectories
add_subdirectory("vendor/benchmarker")
add_subdirectory("vendor/googletest")
add_subdirectory("src")
add_subdirectory("tests")
add_subdirectory("sandbox")
add_subdirectory("benchmarking")