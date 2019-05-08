#ifndef TIME_H
#define TIME_H

#include <chrono>

/**
 * clock class
 * system_clock(C++11)   wall clock time from the system-wide realtime clock
 * steady_clock(C++11)   monotonic clock that will never be adjusted
 * high_resolution_clock(C++11) the clock with the shortest tick period available
 * utc_clock(C++20)  Clock for Coordinated Universal Time (UTC)
 * tai_clock(C++20)  Clock for International Atomic Time (TAI)
 * gps_clock(C++20)  Clock for GPS time
 * file_clock(C++20) Clock used for file time
 * local_t (C++20)  pseudo-clock representing local time
 *
 * is_clock/is_clock_v(C++20)   determines if a type is a Clock
 *
 * (class template)
 * time_point(C++11)   a point in time
 * duration (C++11)  a time interval
 * clock_time_conversion(C++20)  traits class defining how to convert time points of one clock to another
 *
 * (function template)
 * clock_cast (C++20)  convert time points of one clock to another
 *
 */
// clock: static now() return current time point
typedef std::chrono::system_clock Clock;
typedef std::chrono::steady_clock StClock;
typedef std::chrono::high_resolution_clock HrClock;

typedef std::chrono::time_point<Clock> Time;
typedef std::chrono::time_point<StClock> StTime;
typedef std::chrono::time_point<HrClock> HrTime;

typedef std::chrono::milliseconds Duration;  //ms duration

/*
std::chrono::nanoseconds	duration<int64_t, std::nano>
std::chrono::microseconds	duration<int64_t, std::micro>
std::chrono::milliseconds	duration<int64_t, std::milli>
std::chrono::seconds	duration<int64_t>
std::chrono::minutes	duration<int32_t, std::ratio<60>>
std::chrono::hours	duration<int32_t, std::ratio<3600>>
std::chrono::days (since C++20)	duration<int32_t, std::ratio<86400>>
std::chrono::weeks (since C++20)	duration<int32_t, std::ratio<604800>>
std::chrono::months (since C++20)	duration<int32_t, std::ratio<2629746>>
std::chrono::years (since C++20)	duration<int32_t, std::ratio<31556952>>
*/

#endif
