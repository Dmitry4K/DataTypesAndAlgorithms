#pragma once
#include<chrono>
class Timer {
	std::chrono::steady_clock::time_point start_point = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end_point = start_point;
	bool is_stoped = true;
public:
	void Start();
	void Stop();
	long long Time();
};
