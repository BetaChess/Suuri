
#include <benchmark/benchmark.h>
#include <big_int.hpp>

#include <chrono>
#include <iostream>
#include <sstream>

#define STARTSEED 6942069

constexpr uint32_t pcg_hash(uint32_t x)
{
	x = x * 747796405u + 2891336453u;
	uint32_t word = ((x >> ((x >> 28u) + 4u)) ^ x) * 277803737u;
	return (word >> 22) ^ word;
}

float pcg_random(uint32_t &seed)
{
	seed = pcg_hash(seed);
	return float(seed) / float(std::numeric_limits<uint32_t>::max());
}

uint32_t pcg_random(uint32_t &seed, uint32_t min, uint32_t max)
{
	return min + uint32_t(pcg_random(seed) * float(max - min));
}


#define STANDARDPARAMS RangeMultiplier(2)->Range(1, 1 << 18)->UseManualTime()

static void BM_integer_long_multiplication_same_length(benchmark::State &state)
{
	state.SetLabel((std::stringstream{} << state.range(0)).str());

	// REUSABLE VARIABLES
	suuri::big_int_t a, b, c;
	auto generator = [](uint32_t min, uint32_t max) {
		static uint32_t seed = STARTSEED;
		return pcg_random(seed, min, max);
	};

	for (auto _: state)
	{
		// SETUP CODE
		a = suuri::big_int_t::random_of_size(state.range(0), generator);
		b = suuri::big_int_t::random_of_size(state.range(0), generator);

		auto start = std::chrono::high_resolution_clock::now();
		// --- CODE TO BE BENCHMARKED

		c = a.long_multiplication(b);

		// ---
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_integer_long_multiplication_same_length)->STANDARDPARAMS;

static void BM_integer_karatsuba_multiplication_same_length(benchmark::State &state)
{
	state.SetLabel((std::stringstream{} << state.range(0)).str());

	// REUSABLE VARIABLES
	suuri::big_int_t a, b, c;
	auto generator = [](uint32_t min, uint32_t max) {
		static uint32_t seed = STARTSEED;
		return pcg_random(seed, min, max);
	};

	for (auto _: state)
	{
		// SETUP CODE
		a = suuri::big_int_t::random_of_size(state.range(0), generator);
		b = suuri::big_int_t::random_of_size(state.range(0), generator);

		auto start = std::chrono::high_resolution_clock::now();
		// --- CODE TO BE BENCHMARKED

		c = a.karatsuba_multiplication(b);

		// ---
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_integer_karatsuba_multiplication_same_length)->STANDARDPARAMS;


BENCHMARK_MAIN();