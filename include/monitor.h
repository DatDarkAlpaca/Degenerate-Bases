#pragma once
#include "pch.h"

template<typename F, typename... Args>
long long Bench(F f, Args&&... args)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	f(std::forward<Args>(args)...);

	return duration_cast<milliseconds>(high_resolution_clock::now() - t1).count();
}
