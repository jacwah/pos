#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>

namespace util {

/**
 * Represents a point in time.
 */
class Time {
    std::chrono::system_clock::time_point timePoint;

public:
    /**
     * Creates a new instance representing the present time.
     */
    Time()
        : timePoint(std::chrono::system_clock::now())
    {}

    /**
     * Gets the point in time as a libc <code>time_t</code> struct.
     */
    std::time_t getCtime() const
    {
        return std::chrono::system_clock::to_time_t(timePoint);
    }
};

}

/**
 * Appends a string representation in local time of a time into a char stream.
 *
 * @param os The stream.
 * @param time The time.
 * @return The stream.
 */
inline std::ostream& operator<<(std::ostream& os, const util::Time& time)
{
    auto ctime = time.getCtime();
    auto localTime = std::localtime(&ctime);
    os << std::put_time(localTime, "%F %R");
    return os;
}
