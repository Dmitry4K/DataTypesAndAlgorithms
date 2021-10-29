## Simple Timer v2.0
~~It's a my first try to do something like real timer clock~~ Okay, it's not a first attempt, so this pretty file have some updates ^_^.

Let's check how use this class!

### Usage

In this examples I am using namespacing)
```c++
using namespace chrono_timer;
```

#### Object declaration

You can simply do one of this examples

```c++
timer<> my_timer //this timer returns time in nanoseconds
timer<std::chrono::nanoseconds> my_timer2 //same timer that previous
timer<std::chrono::milliseconds> mu_tiemr3 //this timer returns time in milliseconds
```
Allows to use another std::chrono time types, or you can do something like that

```c++
timer_mcs timer // returns microseconds
timer_mls timer // returns milliseconds
//and another)
```

#### Methods

This class has a few methods:

*start()* - remembers the time start point;

*stop()* - remembers the time start point;

*time()* - returns long long number in milliseconds. Returns current time if Start() was called, else returns End - Start time

*measure(void f())* - returns time for function f, also f is executing while time measuring

#### Static functions

Namespace have one static function for measurement

*measure_time_in_nanoseconds(void f())* - returns time in nanoseconds for function f, also f is executing while time measuring

#### Examples

```c++
timer<> timer;
timer.start();
mySuperFunction(228, 322);
timer.stop();
std::cout << timer.time(); //returns nanoseconds
```

```c++
timer<> timer;
timer.start();
mySuperFunction(228, 322);
std::cout << timer.time(); //returns nanoseconds
```

```c++
timer<> timer;
std::cout << timer.measure([](){mySuperFunction(228, 322);}); //returns nanoseconds
```

```c++
timer<std::chrono::milliseconds> timer;
std::cout << timer.measure([](){mySuperFunction(228, 322);}); //returns milliseconds
```

```c++
timer_sec timer;
std::cout << timer.measure([](){mySuperFunction(228, 322);}); //returns seconds
```

```c++
std::cout << measure_time_in_nanoseconds([](){mySuperFunction(228, 322);}); //returns nanoseconds
```
