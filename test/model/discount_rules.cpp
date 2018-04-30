#include "catch.hpp"
#include "model/discount_rules.h"

TEST_CASE("Discount rules")
{
    integration::CustomerId invalidId(-1);
    integration::CustomerId discountedId(1);
    integration::CatalogCreator catalogCreator;
    model::DiscountRules discountRules(catalogCreator);

    SECTION("unregistered customers get no discount")
    {
        model::Discount discount = discountRules.getDiscountFor(invalidId);
        REQUIRE(static_cast<double>(discount.getAmount(util::Amount(10))) == 0.0);
    }

    SECTION("registered customers get a discount")
    {
        model::Discount discount = discountRules.getDiscountFor(discountedId);
        REQUIRE(static_cast<double>(discount.getAmount(util::Amount(10))) > 0.0);
    }
}
