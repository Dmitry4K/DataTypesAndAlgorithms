## Simple Timer
It's a my first try to do something like real timer clock

```c++
class Timer {
	std::chrono::steady_clock::time_point start_point = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end_point = start_point;
	bool is_stoped = true;
public:
	void Start();
	void Stop();
	long long Time();
};
```

This class has a few methods:

*Start()* - starting checking the time

*Stop()* - stops checking the time and saves the end time

*Time()* - returns long long number in milliseconds. Returns current time if Start() was called, else returns End - Start time
