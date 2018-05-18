#include "catch.hpp"
#include "model/shopping_cart.h"

TEST_CASE("Shopping cart works with items")
{
    integration::ItemCatalog itemCatalog;
    integration::ItemId itemId(1);
    integration::ItemId itemId2(2);
    integration::Item item = itemCatalog.find(itemId);
    integration::Item item2 = itemCatalog.find(itemId2);
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
        REQUIRE(cart.begin() == cart.end());
    }

    SECTION("Can add multiple items after inital addition")
    {
        cart.addItem(itemId, 2);
        auto iter = cart.begin();
        CHECK(iter->first == itemId);
        CHECK(iter->second.getQuantity() == 2);
        CHECK(++iter == cart.end());
        cart.addItem(itemId, 2);
        iter = cart.begin();
        CHECK(iter->first == itemId);
        CHECK(iter->second.getQuantity() == 4);
        CHECK(++iter == cart.end());
    }

    SECTION("Gross price and summary is correct")
    {
        util::Amount correctPrice = item.getPrice() * 3 + item2.getPrice() * 4;
        auto summary = cart.addItem(itemId, 3);
        CHECK(summary.getLastAddedItem().getDescription() == item.getDescription());
        CHECK(summary.getLastAddedItem().getPrice() == item.getPrice());
        summary = cart.addItem(itemId2, 4);
        CHECK(summary.getLastAddedItem().getDescription() == item2.getDescription());
        CHECK(summary.getLastAddedItem().getPrice() == item2.getPrice());
        CHECK(cart.calculateGrossPrice() == Approx(correctPrice));
        CHECK(summary.getGrossPrice() == Approx(correctPrice));
    }

    SECTION("Still empty after invalid add")
    {
        integration::ItemId invalidId(0);

        REQUIRE_THROWS_AS(
            cart.addItem(invalidId, 1),
            integration::InvalidItemIdException
        );

        CHECK(cart.calculateGrossPrice() == 0.0);
        CHECK(cart.begin() == cart.end());
    }
}
