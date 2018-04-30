#pragma once

#include "controller/sale_controller_factory.h"
#include "model/shopping_cart_factory.h"

namespace view {

/**
 * A terminal interface for the system.
 */
class TerminalView {
    controller::SaleControllerFactory saleControllerFactory;
    model::ShoppingCartFactory shoppingCartFactory;

public:
    /**
     * Creates a new instance.
     *
     * @param saleControllerFactory A factory from which any
     *                              {@link controller::SaleController}
     *                              instances will be created.
     * @param shoppingCartFactory A factory from which any
     *                            {@link model::ShoppingCart} instances
     *                            will be created.
     */
    TerminalView(
            controller::SaleControllerFactory saleControllerFactory,
            model::ShoppingCartFactory shoppingCartFactory)
        : saleControllerFactory(saleControllerFactory)
        , shoppingCartFactory(shoppingCartFactory)
    {}

    /**
     * Run the interface in an endless loop.
     */
    void runLoop();

    /**
     * Run the interface for a single sale.
     */
    void runSingle();
};

}