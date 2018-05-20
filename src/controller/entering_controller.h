#pragma once

#include "controller/sale_controller.h"
#include "controller/sale_controller_builder.h"
#include "controller/operation_failed_exception.h"
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
     * @throws OperationFailedException If the operation failed for any other
     *                                  reason.
     */
    model::ShoppingCartSummary enterItem(integration::ItemId id, int quantity)
    {
        try {
            return shoppingCart.addItem(id, quantity);
        } catch (integration::DatabaseErrorException& databaseError) {
            throw OperationFailedException("Database error");
        }
    }

    /**
     * Creates a {@link controller::SaleController} for administering
     * the sale of items added so far.
     *
     * @param builder A builder used to create new
     *                {@link controller::SaleController} instances.
     * @return A {@link controller::SaleController} for the items added so far.
     */
    SaleController finish(SaleControllerBuilder builder)
    {
        return builder.build(shoppingCart);
    }
};

}

