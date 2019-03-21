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
typedef std::chrono::high_resolution_clock HrClock; // maybe the same as Clock

typedef Clock::duration Duration; // in units of ns
typedef StClock::duration StDuration;
typedef HrClock::duration HrDuration; 

typedef Clock::time_point Time;
typedef StClock::time_point StTime;
typedef HrClock::time_point HrTime;

inline Time now() { return Clock::now(); }
inline StTime stNow() { return StClock::now(); }
inline HrTime hrNow() { return HrClock::now(); }

inline Duration duration(const Time & t0 ) { return Clock::now() - t0; }
inline StDuration stDuration(const StTime & t0 ) { return StClock::now() - t0; }
//inline HrDuration hrDuration(const HrTime & t0 ) { return HrClock::now() - t0; }

inline std::ostream & operator<<(std::ostream & oss, const Time & t0)
{
  std::time_t t = Clock::to_time_t(t0);
  //oss << std::ctime(&t);  // output: Thu Mar 21 05:55:51 2019\n
  oss << std::put_time(std::localtime(&t), "%F %T"); //2019-03-21 06:09:34 ISO 8601 Date(%Y-%m-%d) Time(%H:%M:%S) format
  return oss;
}


#endif
