#include "catch.hpp"
#include "util/amount.h"
#include <sstream>

TEST_CASE("Amount is default initialized to zero")
{
    util::Amount amount;
    REQUIRE(static_cast<double>(amount) == 0);
}

TEST_CASE("Amount is initialized to given value")
{
    util::Amount amount(5);
    REQUIRE(static_cast<double>(amount) == 5);
}

TEST_CASE("Amounts can be compared")
{
    util::Amount small(5);
    util::Amount large(10);
    REQUIRE(small < large);
    REQUIRE_FALSE(small < small);
    REQUIRE_FALSE(large < small);
}

TEST_CASE("Amount can be multiplied by scalar")
{
    util::Amount five(5);
    util::Amount ten = five * 2;

    REQUIRE(static_cast<double>(ten) == Approx(10));
}

TEST_CASE("Amounts implement basic mathematical operators")
{
    util::Amount five(5);
    util::Amount two(2);

    SECTION("addition")
    {
        util::Amount seven = five + two;
        REQUIRE(static_cast<double>(seven) == Approx(7));
    }

    SECTION("subtraction")
    {
        util::Amount three = five - two;
        REQUIRE(static_cast<double>(three) == Approx(3));
    }

    SECTION("addition assignment")
    {
        util::Amount amount = five;
        amount += two;
        REQUIRE(static_cast<double>(amount) == Approx(7));
    }
}

TEST_CASE("Amount implements ostream interface")
{
    util::Amount one(1);
    std::stringstream stream;
    stream << one;
    REQUIRE(stream.str() == "$1");
}
