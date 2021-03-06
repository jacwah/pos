#include "catch.hpp"
#include "integration/dto.h"
#include "integration/item_catalog.h"
#include "model/shopping_cart_factory.h"
#include "model/shopping_cart_summary.h"
#include "model/shopping_cart.h"
#include "controller/entering_controller.h"

TEST_CASE("Entering controller")
{
    integration::CatalogCreator catalogCreator;
    model::ShoppingCartFactory cartFactory(catalogCreator);
    controller::EnteringController enteringController(cartFactory);
    integration::ItemId validItemId(1);
    integration::ItemId invalidItemId(0);

    SECTION("Adding a valid item")
    {
        integration::Item expectedItem = catalogCreator.getItemCatalog().find(validItemId);
        model::ShoppingCartSummary summary =
            enteringController.enterItem(validItemId, 1);

        SECTION("Correct lastAddedItem")
        {
            integration::Item addedItem = summary.getLastAddedItem();
            CHECK(addedItem.getDescription() == expectedItem.getDescription());
            CHECK(addedItem.getPrice() == expectedItem.getPrice());
        }

        SECTION("Correct gross price")
        {
            REQUIRE(summary.getGrossPrice() == Approx(expectedItem.getPrice()));
        }
    }

    SECTION("Adding an invalid item")
    {
        CHECK_THROWS_AS(
            enteringController.enterItem(invalidItemId, 1),
            integration::InvalidItemIdException
        );
    }
}
