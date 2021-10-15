#pragma once
#include<chrono>

namespace chrono_timer {
    template<class T = std::chrono::nanoseconds>
    class timer {
        std::chrono::steady_clock::time_point start_point = std::chrono::high_resolution_clock::now();
        std::chrono::steady_clock::time_point end_point = start_point;
        bool is_stoped = true;
    public:
        using time_type = T;
        void Start() {
            start_point = std::chrono::high_resolution_clock::now();
            is_stoped = false;
        }
        void Stop() {
            end_point = std::chrono::high_resolution_clock::now();
            is_stoped = true;
        }
        long long Time() {
            return is_stoped ? std::chrono::duration_cast<time_type>(end_point - start_point).count() : std::chrono::duration_cast<time_type>(std::chrono::high_resolution_clock::now() - start_point).count();
        }
    };
    long long nanosecondsTime(void f(void)) {
        timer<> timer;
        timer.Start();
        f();
        return timer.Time();
    }
};
