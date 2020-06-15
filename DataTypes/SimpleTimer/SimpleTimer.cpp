#include"SimpleTimer.h"
void Timer::Start() {
	start_point = std::chrono::high_resolution_clock::now();
	is_stoped = false;
}

void Timer::Stop() {
	end_point = std::chrono::high_resolution_clock::now();
	is_stoped = true;
}

long long Timer::Time() {
	return is_stoped ? std::chrono::duration_cast<std::chrono::milliseconds>(end_point - start_point).count() : std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_point).count();
}
