#pragma once

#include "controller/sale_controller.h"
#include "controller/sale_controller_factory.h"
#include "model/shopping_cart_factory.h"
#include "model/shopping_cart.h"
#include "integration/dto.h"

namespace controller {

/**
 * Controller class for mediating the entering of items between views and the
 * model.
 */
class EnteringController {
    model::ShoppingCart shoppingCart;

public:
    /**
     * Creates a new instance.
     *
     * @param shoppingCartFactory A factory used to create new
     *                            {@link model::ShoppingCart} instances.
     */
    EnteringController(model::ShoppingCartFactory shoppingCartFactory)
        : shoppingCart(shoppingCartFactory.createCart())
    {}

    /**
     * Adds an item of specified quantity.
     *
     * @param id An identifier for the item to be added.
     * @param quantity Specifies the number of items to be added.
     * @return A summary of the items added so far.
     * @throws InvalidItemIdException If the requested item could not be found.
     */
    model::ShoppingCartSummary enterItem(integration::ItemId id, int quantity)
    {
        return shoppingCart.addItem(id, quantity);
    }

    /**
     * Creates a {@link controller::SaleController} for administering
     * the sale of items added so far.
     *
     * @param factory A factory used to create new
     *                {@link controller::SaleController} instances.
     * @return A {@link controller::SaleController} for the items added so far.
     */
    SaleController finish(SaleControllerFactory factory)
    {
        return factory.create(shoppingCart);
    }
};

}

