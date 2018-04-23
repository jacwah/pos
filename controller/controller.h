#pragma once

#include <experimental/optional>
#include <cassert>
#include "model/shopping_cart_factory.h"
#include "model/shopping_cart.h"
#include "model/discount_rules.h"
#include "model/sale_log.h"

namespace controller {

class Controller {
    model::ShoppingCartFactory cartFactory;
    model::DiscountRules discountRules;
    model::SaleLog saleLog;

    std::experimental::optional<model::ShoppingCart> shoppingCart;
    //Sale sale;

    public:
    Controller(model::ShoppingCartFactory cartFactory, model::DiscountRules discountRules, model::SaleLog&& saleLog)
        : cartFactory(cartFactory)
        , discountRules(discountRules)
        , saleLog(std::move(saleLog))
        , shoppingCart({})
        {}

    void startSale()
    {
        assert(!shoppingCart);
        shoppingCart = std::experimental::make_optional(cartFactory.createCart());
    }

    model::ShoppingCartSummary enterItem(integration::ItemId id, int quantity)
    {
        return shoppingCart->addIfValid(id, quantity);
    }
};

}
