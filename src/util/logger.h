#pragma once

#include <fstream>

namespace util {

class Logger {
    std::fstream logFile;
    Logger(const char *filename);

public:
    static Logger& getInstance();
    void logException(const std::exception& exception);
};

}
