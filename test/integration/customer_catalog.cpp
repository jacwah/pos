#include "catch.hpp"
#include "integration/customer_catalog.h"

TEST_CASE("Customer catalog")
{
    integration::CustomerCatalog customerCatalog;

    SECTION("Finds valid ids")
    {
        integration::CustomerId validId(1);
        util::optional<integration::Customer> customer = customerCatalog.find(validId);
        REQUIRE(customer);
    }

    SECTION("Does not find invalid ids")
    {
        integration::CustomerId invalidId(0);
        util::optional<integration::Customer> customer = customerCatalog.find(invalidId);
        REQUIRE_FALSE(customer);
    }
}
