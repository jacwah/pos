#include "catch.hpp"
#include "integration/item_catalog.h"

TEST_CASE("Item catalog")
{
    integration::ItemCatalog itemCatalog;

    SECTION("Finds valid ids")
    {
        integration::ItemId validId(1);
        REQUIRE_NOTHROW(itemCatalog.find(validId));
    }

    SECTION("Does not find invalid ids")
    {
        integration::ItemId invalidId(0);

        SECTION("Correct message")
        {
            REQUIRE_THROWS_WITH(
                itemCatalog.find(invalidId),
                "Could not find item 0"
            );
        }

        SECTION("Correct type")
        {
            REQUIRE_THROWS_AS(
                itemCatalog.find(invalidId),
                integration::InvalidItemIdException
            );
        }
    }
}
