#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>

namespace util {

class Time {
    std::chrono::system_clock::time_point timePoint;

public:
    Time() : timePoint(std::chrono::system_clock::now()) {}

    std::time_t getCtime() const
    {
        return std::chrono::system_clock::to_time_t(timePoint);
    }
};

}

inline std::ostream& operator<<(std::ostream& os, const util::Time& time)
{
    auto ctime = time.getCtime();
    auto localTime = std::localtime(&ctime);
    os << std::put_time(localTime, "%F %R");
    return os;
}
