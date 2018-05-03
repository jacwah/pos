#include "catch.hpp"
#include "integration/inventory_system.h"
#include <sstream>

TEST_CASE("Inventory system gives correct output")
{
    std::stringstream stream;
    integration::InventorySystem inventorySystem(stream);

    SECTION("Nothing sold")
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
        inventorySystem.handleSaleEvent(event);
        REQUIRE(stream.str() == "Sending sale information (0 items) to external inventory system...\n");
    }

    SECTION("One item sold")
    {
        util::Amount price(5);
        integration::ItemId itemId(1);
        integration::Item item("Test item", price);
        integration::SoldItemRecord soldItem(itemId, item, 1, price);
        integration::SaleEvent event(
            {soldItem},
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            price,
            util::Amount(0),
            util::Amount(0)
        );

        inventorySystem.handleSaleEvent(event);
        REQUIRE(stream.str() == "Sending sale information (1 items) to external inventory system...\n");
    }
}
