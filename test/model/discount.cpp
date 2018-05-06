#include "catch.hpp"
#include "model/discount.h"

TEST_CASE("Default discount is a no-op")
{
    model::Discount none;
    util::Amount zero(0), ten(10);

    SECTION("On zero")
    {
        REQUIRE(none.applyTo(zero) == 0.0);
    }

    SECTION("On ten")
    {
        REQUIRE(none.applyTo(ten) == 10.0);
    }
}

TEST_CASE("Discounts can be used on amounts")
{
    util::Percentage quarter(0.25);
    model::Discount quarterOff(quarter);
    util::Amount ten(10);

    SECTION("applied to")
    {
        REQUIRE(quarterOff.applyTo(ten) == Approx(7.5));
    }

    SECTION("calculate discount amount")
    {
        REQUIRE(quarterOff.getAmount(ten) == Approx(2.5));
    }
}
