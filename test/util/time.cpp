#include "catch.hpp"
#include "util/time.h"
#include <sstream>

TEST_CASE("Time is printed with correct format")
{
    util::Time now;
    std::stringstream stream;
    stream << now;
    REQUIRE_THAT(stream.str(),
            Catch::Matches("\\d\\d\\d\\d-\\d\\d-\\d\\d \\d\\d:\\d\\d"));
}
