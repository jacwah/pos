#include "view/error_message_handler.h"
#include "util/time.h"
#include <iostream>

void view::ErrorMessageHandler::displayError(const char *message)
{
    util::Time now;
    std::cout
        << "[" << now << "] "
        << "Error: "
        << message
        << std::endl;
}
