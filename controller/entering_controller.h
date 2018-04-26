#pragma once

#include "model/shopping_cart_factory.h"
#include "model/shopping_cart.h"
#include "integration/dto.h"

namespace controller {

class EnteringController {
    model::ShoppingCart shoppingCart;

public:
    EnteringController(model::ShoppingCartFactory shoppingCartFactory)
        : shoppingCart(shoppingCartFactory.createCart())
    {}

    model::ShoppingCartSummary enterItem(integration::ItemId id, int quantity)
    {
        return shoppingCart.addIfValid(id, quantity);
    }

    SaleController finish(SaleControllerFactory factory)
    {
        return factory.create(shoppingCart);
    }
};

}

