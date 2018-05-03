#include "catch.hpp"
#include "model/shopping_cart.h"

TEST_CASE("Shopping cart works with items")
{
    integration::ItemCatalog itemCatalog;
    integration::ItemId itemId(1);
    integration::Item item = *itemCatalog.find(itemId);
    model::ShoppingCart cart(itemCatalog);

    SECTION("ItemRecords can increment quantity")
    {
        model::ItemRecord record(item, 0);
        REQUIRE(record.getQuantity() == 0);
        record.incrementQuantity(1);
        REQUIRE(record.getQuantity() == 1);
    }

    SECTION("Cart is empty by default")
    {
        FAIL("Not tested");
    }

    SECTION("Can add multiple items after inital addition")
    {
        cart.addIfValid(itemId, 2);
        auto iter = cart.begin();
        REQUIRE(iter->first == itemId);
        REQUIRE(iter->second.getQuantity() == 2);
        REQUIRE(++iter == cart.end());
        cart.addIfValid(itemId, 2);
        iter = cart.begin();
        REQUIRE(iter->first == itemId);
        REQUIRE(iter->second.getQuantity() == 4);
        REQUIRE(++iter == cart.end());
    }
}
