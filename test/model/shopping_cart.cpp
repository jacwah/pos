#include "catch.hpp"
#include "model/shopping_cart.h"

TEST_CASE("Shopping cart works with items")
{
    integration::ItemCatalog itemCatalog;
    integration::ItemId itemId(1);
    integration::ItemId itemId2(2);
    integration::ItemId invalidId(0);
    integration::Item item = *itemCatalog.find(itemId);
    integration::Item item2 = *itemCatalog.find(itemId2);
    model::ShoppingCart cart(itemCatalog);
    model::ShoppingCartSummary summary({}, {});

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
        cart.addIfValid(itemId, 2);
        auto iter = cart.begin();
        CHECK(iter->first == itemId);
        CHECK(iter->second.getQuantity() == 2);
        CHECK(++iter == cart.end());
        cart.addIfValid(itemId, 2);
        iter = cart.begin();
        CHECK(iter->first == itemId);
        CHECK(iter->second.getQuantity() == 4);
        CHECK(++iter == cart.end());
    }

    SECTION("Gross price and summary is correct")
    {
        util::Amount correctPrice = item.getPrice() * 3 + item2.getPrice() * 4;
        summary = cart.addIfValid(itemId, 3);
        CHECK(summary.getLastAddedItem()->getDescription() == item.getDescription());
        CHECK(summary.getLastAddedItem()->getPrice() == item.getPrice());
        summary = cart.addIfValid(itemId2, 4);
        CHECK(summary.getLastAddedItem()->getDescription() == item2.getDescription());
        CHECK(summary.getLastAddedItem()->getPrice() == item2.getPrice());
        CHECK(cart.calculateGrossPrice() == Approx(correctPrice));
        CHECK(summary.getGrossPrice() == Approx(correctPrice));
    }

    SECTION("Invalid id is indicated with no last added")
    {
        summary = cart.addIfValid(invalidId, 1);
        CHECK_FALSE(summary.getLastAddedItem());
        CHECK(summary.getGrossPrice() == util::Amount(0));
    }
}
