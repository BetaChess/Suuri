
#include <big-int.h>
#include <suurimath.h>

#include <benchmarker.h>

#include <iostream>
#include <random>
#include <vector>
#include <chrono>

using testT = uint64_t;

volatile testT dontOpt;

std::vector<testT> a, b;
size_t count = 0;

inline void powWrap()
{
	BENCHMARK_START(std_pow_benchmark);
	dontOpt = std::pow<testT>(a[count], b[count]);
}

inline void suuriPowWrap()
{
	BENCHMARK_START(suuri_pow_benchmark);
	dontOpt = suuri::integer::pow<testT>(a[count], b[count]);
}

inline void suuriConstWrap()
{
	BENCHMARK_START(suuri_const_benchmark);
	dontOpt = suuri::integer::pow<testT, 7ULL>(b[count]);
}

std::vector<void(*)()> funcList = {powWrap, suuriPowWrap, suuriConstWrap};


int main()
{	
	/*std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 30);*/

	// obtain a time-based seed:
	const uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();

	const testT aMax = 3;
	const testT bMax = 40;
	const size_t sizes = 100000;
	a.resize(sizes);
	b.resize(sizes);

	// Create list a
	for (size_t i = 0; i < a.size(); i++)
		a[i] = static_cast<testT>((static_cast<float>(i) / a.size()) * aMax + 1ULL);

	// Create list b
	for (size_t i = 0; i < a.size(); i++)
		b[i] = static_cast<testT>((static_cast<float>(i) / b.size()) * (bMax + 1ULL));
	
	const size_t runsPerTest = 1500;

	// Run tests forward
	for (size_t i = 0; i < runsPerTest; i++)
	{
		count = 0;

		for (; count < sizes; count++)
		{
			std::shuffle(funcList.begin(), funcList.end(), std::default_random_engine(seed));
			for (auto& func : funcList)
				func();
		}
	}
	// Run tests backward
	for (size_t i = 0; i < runsPerTest; i++)
	{
		count = sizes;

		while (count)
		{
			count--;
			std::shuffle(funcList.begin(), funcList.end(), std::default_random_engine(seed));
			for (auto& func : funcList)
				func();
		}
	}
	// Run random data shuffle tests
	for (size_t i = 0; i < runsPerTest; i++)
	{
		count = 0;
		std::shuffle(a.begin(), a.end(), std::default_random_engine(seed));
		std::shuffle(b.begin(), b.end(), std::default_random_engine(seed));
		for (; count < sizes; count++)
		{
			std::shuffle(funcList.begin(), funcList.end(), std::default_random_engine(seed));
			for (auto& func : funcList)
				func();
		}
	}
	

	Benchmarker::printStats();
	
	return 0;
}
