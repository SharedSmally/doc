#ifndef CPW_TIME_H
#define CPW_TIME_H

#include <iostream>
#include <chrono>
#include <ctime>
/*
system_clock (C++11) wall clock time from the system-wide realtime clock (class)
steady_clock (C++11) monotonic clock that will never be adjusted (class)
high_resolution_clock (C++11) the clock with the shortest tick period available (class)
is_clock/is_clock_v (C++20) determines if a type is a Clock 
(class template) (variable template)
utc_clock (C++20) Clock for Coordinated Universal Time (UTC) (class)
tai_clock (C++20) Clock for International Atomic Time (TAI) (class)
gps_clock (C++20) Clock for GPS time (class)
file_clock(C++20)Clock used for file time (typedef)
local_t (C++20) pseudo-clock representing local time 
*/
typedef std::chrono::system_clock Clock;
typedef std::chrono::steady_clock StClock;
typedef std::chrono::high_resolution_clock HrClock;

typedef Clock::duration Duration;
typedef StClock::duration StDuration;
typedef StClock::duration HrDuration;

typedef Clock::time_point Time;
typedef StClock::time_point StTime;
typedef HrClock::time_point HrTime;

/*
typedef std::chrono::time_point< Clock > Time;
typedef std::chrono::time_point< StClock > StTime;
typedef std::chrono::time_point< HrClock > HrTime;
*/


#endif
