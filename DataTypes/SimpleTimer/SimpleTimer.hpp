#pragma once
#include<chrono>
class Timer {
	std::chrono::steady_clock::time_point start_point = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end_point = start_point;
	bool is_stoped = true;
public:
	void Start(){
    start_point = std::chrono::high_resolution_clock::now();
    is_stoped = false;
  }
	void Stop(){
    end_point = std::chrono::high_resolution_clock::now();
    is_stoped = true;
  }
	long long Time(){
    return is_stoped ? std::chrono::duration_cast<std::chrono::milliseconds>(end_point - start_point).count() : std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_point).count();
  }
}
