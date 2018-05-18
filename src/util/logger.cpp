#include "util/logger.h"
#include "util/time.h"

util::Logger::Logger(const char *filename)
{
    logFile = {};
    logFile.open(
            filename,
            std::ios_base::out | std::ios_base::app);
}

util::Logger& util::Logger::getInstance()
{
    static util::Logger logger("exceptions.txt");
    return logger;
}

void util::Logger::logException(const std::exception& exception)
{
    util::Time now;

    logFile
        << "[" << now << "] "
        << "Caught exception: "
        << exception.what()
        << std::endl;
}
