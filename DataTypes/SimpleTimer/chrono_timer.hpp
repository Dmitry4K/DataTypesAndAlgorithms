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
        void start() {
            start_point = std::chrono::high_resolution_clock::now();
            is_stoped = false;
        }
        void stop() {
            end_point = std::chrono::high_resolution_clock::now();
            is_stoped = true;
        }
        long long time() {
            return is_stoped ? std::chrono::duration_cast<time_type>(end_point - start_point).count() : std::chrono::duration_cast<time_type>(std::chrono::high_resolution_clock::now() - start_point).count();
        }
        long long measure(void f(void)) {
            this->start();
            f();
            return this->time();
        }
    };
    long long nanoseconds_time(void f(void)) {
        timer<> timer;
        timer.start();
        f();
        return timer.time();
    }

    template<class T>
    long long measure_time(void f(void)) {
        timer<T> timer;
        timer.start();
        f();
        return timer.time();
    }

    using timer_nns = timer <>;
    using timer_mls = timer < std::chrono::milliseconds >;
    using timer_mcs = timer < std::chrono::microseconds >;
    using timer_sec = timer < std::chrono::seconds >;
    using timer_min = timer < std::chrono::minutes >;
};
