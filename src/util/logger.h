#pragma once

#include <fstream>

namespace util {

/**
 * Logs messages to a file aimed at sysadmins and developers.
 */
class Logger {
    std::fstream logFile;
    Logger(const char *filename);

public:
    /**
     * Gets the single instance.
     *
     * @return The single instance.
     */
    static Logger& getInstance();

    /**
     * Logs an exception to the file.
     *
     * @param exception The exception.
     */
    void logException(const std::exception& exception);
};

}
