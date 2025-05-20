#pragma once

namespace Core
{
    // simulation of Windows GetTickCount()
    long long GetTickCount();
    /*
    // Clock built upon Windows GetTickCount()
    struct TickCountClock
    {
        typedef unsigned long long                       rep;
        typedef std::milli                               period;
        typedef std::chrono::duration<rep, period>       duration;
        typedef std::chrono::time_point<TickCountClock>  time_point;
        static const bool is_steady = true;

        static time_point now() //noexcept
        {
            return time_point(duration(GetTickCount()));
        }
    };
	*/// Clock built upon Windows GetTickCount64()
}//namespace Core