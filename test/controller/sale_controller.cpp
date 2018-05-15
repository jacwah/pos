#include "catch.hpp"
#include "controller/sale_controller.h"

TEST_CASE("Sale controller")
{
    integration::CatalogCreator catalogCreator;
    model::DiscountRules discountRules(catalogCreator);
    model::SaleLog saleLog;
    model::ShoppingCart shoppingCart(catalogCreator.getItemCatalog());
    integration::CustomerId validCustomerId(1);

    SECTION("With items")
    {
        integration::ItemId validItemId(1);
        shoppingCart.addItem(validItemId, 1);
        controller::SaleController saleController(
                shoppingCart,
                discountRules,
                saleLog);

        SECTION("Without discount")
        {
            SECTION("Net price above zero")
            {
                REQUIRE(util::Amount(0) < saleController.getNetPrice());
            }

            SECTION("Must pay")
            {
                auto change = saleController.payAndGetChange(util::Amount(0));
                REQUIRE_FALSE(change);
            }
        }

        SECTION("With discount")
        {
            SECTION("Net price is lower")
            {
                util::Amount netPriceBeforeDiscount = saleController.getNetPrice();
                saleController.requestDiscount(validCustomerId);
                REQUIRE(saleController.getNetPrice() < netPriceBeforeDiscount);
            }

            SECTION("Must pay")
            {
                saleController.requestDiscount(validCustomerId);
                auto change = saleController.payAndGetChange(util::Amount(0));
                REQUIRE_FALSE(change);
            }
        }
    }

    SECTION("Without items")
    {
        controller::SaleController saleController(
                shoppingCart,
                discountRules,
                saleLog);

        SECTION("Without discount")
        {
            SECTION("Net price is zero")
            {
                REQUIRE(saleController.getNetPrice() == 0.0);
            }

            SECTION("Change is zero")
            {
                auto change = saleController.payAndGetChange(util::Amount(0));
                REQUIRE(change);
                REQUIRE(*change == 0.0);
            }
        }

        SECTION("With discount")
        {
            saleController.requestDiscount(validCustomerId);

            SECTION("Net price is zero")
            {
                REQUIRE(saleController.getNetPrice() == 0.0);
            }

            SECTION("Change is zero")
            {
                auto change = saleController.payAndGetChange(util::Amount(0));
                REQUIRE(change);
                REQUIRE(*change == 0.0);
            }
        }
    }
}
