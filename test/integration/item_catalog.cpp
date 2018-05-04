#include "catch.hpp"
#include "integration/item_catalog.h"

TEST_CASE("Item catalog")
{
    integration::ItemCatalog itemCatalog;

    SECTION("Finds valid ids")
    {
        integration::ItemId validId(1);
        util::optional<integration::Item> item = itemCatalog.find(validId);
        REQUIRE(item);
    }

    SECTION("Does not find invalid ids")
    {
        integration::ItemId invalidId(0);
        util::optional<integration::Item> item = itemCatalog.find(invalidId);
        REQUIRE_FALSE(item);
    }
}
