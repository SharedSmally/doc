## C++11 chrono library
The chrono library defines three main types (durations, clocks, and time points), utility functions and common typedefs.
- Defined in header <chrono> and namespace std::chrono

- Duration (a time interval: class template)

A duration consists of a span of time, defined as some number of ticks of some time unit. For example, "42 seconds" could be represented by a duration consisting of 42 ticks of a 1-second time unit.

- Clocks (class)

A clock consists of a starting point (or epoch) and a tick rate. For example, a clock may have an epoch of January 1, 1970 and tick every second. C++ defines three clock types:

   -  system_clock: wall clock time from the system-wide realtime clock 
   -  steady_clock: monotonic clock that will never be adjusted 
   -  high_resolution_clock: the clock with the shortest tick period available 

- Time point (a point in time : class template)

A time point is a duration of time that has passed since the epoch of specific clock.

 

