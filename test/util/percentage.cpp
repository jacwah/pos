#include "catch.hpp"
#include "util/percentage.h"

TEST_CASE("Percentage can be converted to double")
{
    util::Percentage half(0.5);
    REQUIRE(static_cast<double>(half) == Approx(0.5));
}

TEST_CASE("Percentage can be used with amount")
{
    util::Percentage none(0.0);
    util::Percentage quater(0.25);
    util::Percentage half(0.5);
    util::Percentage all(1.0);

    util::Amount zero(0);
    util::Amount ten(10);

    SECTION("deduction")
    {
        SECTION("0%")
        {
            CHECK(static_cast<double>(none.deductFrom(zero)) == 0.0);
            CHECK(static_cast<double>(none.deductFrom(ten)) == 10.0);
        }

        SECTION("25%")
        {
            CHECK(static_cast<double>(quater.deductFrom(zero)) == 0.0);
            CHECK(static_cast<double>(quater.deductFrom(ten)) == Approx(7.5));
        }

        SECTION("50%")
        {
            CHECK(static_cast<double>(half.deductFrom(zero)) == 0.0);
            CHECK(static_cast<double>(half.deductFrom(ten)) == Approx(5.0));
        }

        SECTION("100%")
        {
            CHECK(static_cast<double>(all.deductFrom(zero)) == 0.0);
            CHECK(static_cast<double>(all.deductFrom(ten)) == Approx(0.0));
        }
    }

    SECTION("addition")
    {
        SECTION("0%")
        {
            CHECK(static_cast<double>(none.addTo(zero)) == 0.0);
            CHECK(static_cast<double>(none.addTo(ten)) == 10.0);
        }

        SECTION("25%")
        {
            CHECK(static_cast<double>(quater.addTo(zero)) == 0.0);
            CHECK(static_cast<double>(quater.addTo(ten)) == Approx(12.5));
        }

        SECTION("50%")
        {
            CHECK(static_cast<double>(half.addTo(zero)) == 0.0);
            CHECK(static_cast<double>(half.addTo(ten)) == Approx(15.0));
        }

        SECTION("100%")
        {
            CHECK(static_cast<double>(all.addTo(zero)) == 0.0);
            CHECK(static_cast<double>(all.addTo(ten)) == Approx(20.0));
        }
    }

    SECTION("application")
    {
        SECTION("0%")
        {
            CHECK(static_cast<double>(none.applyTo(zero)) == 0.0);
            CHECK(static_cast<double>(none.applyTo(ten)) == 0.0);
        }

        SECTION("25%")
        {
            CHECK(static_cast<double>(quater.applyTo(zero)) == 0.0);
            CHECK(static_cast<double>(quater.applyTo(ten)) == Approx(2.5));
        }

        SECTION("50%")
        {
            CHECK(static_cast<double>(half.applyTo(zero)) == 0.0);
            CHECK(static_cast<double>(half.applyTo(ten)) == Approx(5.0));
        }

        SECTION("100%")
        {
            CHECK(static_cast<double>(all.applyTo(zero)) == 0.0);
            CHECK(static_cast<double>(all.applyTo(ten)) == 10.0);
        }
    }
}
