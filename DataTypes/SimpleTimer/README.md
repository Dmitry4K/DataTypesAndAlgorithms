## Simple Timer v2.0
~~It's a my first try to do something like real timer clock~~ Okay, it's not a first attempt, so this pretty file have some updates ^_^.

Let's check how use this class!

### Usage

#### object declaration

You can simply do one of this examples

```
timer<> my_timer //this timer returns time in nanoseconds
timer<std::chrono::nanoseconds> my_timer2 //same timer that previous
timer<std::chrono::milliseconds> mu_tiemr3 //this timer returns time in milliseconds
```
Allows to use another std::chrono time types, or you can do something like that

```
timer_mcs timer // returns microseconds
timer_mls timer // returns milliseconds
//and another)
```

#### Methods

This class has a few methods:

*start()* - remembers the time start point;
*stop()* - remembers the time start point;

*time()* - returns long long number in milliseconds. Returns current time if Start() was called, else returns End - Start time
