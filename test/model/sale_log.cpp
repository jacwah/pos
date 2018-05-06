#include "catch.hpp"
#include "model/sale_log.h"
#include "helper/mock_observer.h"

TEST_CASE("Sale log")
{
    model::SaleLog saleLog;
    int numEvents0 = 0;
    int numEvents1 = 0;
    util::optional<integration::SaleEvent> lastEvent0;
    util::optional<integration::SaleEvent> lastEvent1;
    saleLog.observe(std::make_unique<MockObserver>(numEvents0, lastEvent0));
    saleLog.observe(std::make_unique<MockObserver>(numEvents1, lastEvent1));

    SECTION("Events are broadcast to all observers")
    {
        integration::SaleEvent event(
            {},
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0)
        );
        CHECK(numEvents0 == 0);
        CHECK(numEvents1 == 0);
        CHECK_FALSE(lastEvent0);
        CHECK_FALSE(lastEvent1);

        saleLog.append(event);

        CHECK(numEvents0 == 1);
        CHECK(numEvents1 == 1);
        CHECK(lastEvent0);
        CHECK(lastEvent1);
    }
}
