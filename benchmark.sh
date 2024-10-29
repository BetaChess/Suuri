#!/bin/bash

# Create and navigate to the build directory
mkdir -p build
cd build || exit

# Run cmake to generate build files in Release mode
cmake -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LIBPFM:BOOL=ON ..

# Build the benchmark project
cmake --build . --target all_benchmarks

# Define the output directory and ensure it exists
output_dir="$(pwd)/../benchmark_data/integer/$(hostname)"
mkdir -p "$output_dir"

# Run the benchmark executable with the specified parameters
./benchmark/integer/integer_benchmark --benchmark_out_format=json --benchmark_out="$output_dir/integer_$(date +'%y-%m-%d_%H-%M-%S').json" --benchmark_perf_counters=CYCLES,INSTRUCTIONS,BRANCHES,BRANCH-MISSES,cache-misses