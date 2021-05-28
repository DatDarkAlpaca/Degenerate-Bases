#pragma once
#include "pch.h"

template<typename F, typename... Args>
long long Bench(F f, Args&&... args)
{
	high_resolution_clock::time_point begin = high_resolution_clock::now();

	f(std::forward<Args>(args)...);

	return duration_cast<nanoseconds>(high_resolution_clock::now() - begin).count() / 1000000;
}
