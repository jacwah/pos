#include "catch.hpp"
#include "integration/sale_observer_creator.h"

TEST_CASE("createSaleObservers creates 3 observers")
{
    auto observers = integration::createSaleObservers();
    REQUIRE(observers.size() == 3);
}
