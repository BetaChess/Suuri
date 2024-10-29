cmake_minimum_required(VERSION 3.8)

project(suuri_benchmark)

# Include sub-projects.
add_subdirectory(integer)

# Custom target to build all benchmarks
add_custom_target(all_benchmarks)
add_dependencies(all_benchmarks integer_benchmark)