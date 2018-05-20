#pragma once

#include "controller/sale_controller_builder.h"
#include "model/shopping_cart_factory.h"
#include "view/error_message_handler.h"

namespace view {

/**
 * A terminal interface for the system.
 */
class TerminalView {
    controller::SaleControllerBuilder& saleControllerBuilder;
    model::ShoppingCartFactory& shoppingCartFactory;
    view::ErrorMessageHandler errorMessageHandler;

    void handleSystemError(const char *userMessage, const std::exception& exception);
    util::optional<int> getAndParseInt();

public:
    /**
     * Creates a new instance.
     *
     * @param saleControllerBuilder A builder from which any
     *                              {@link controller::SaleController}
     *                              instances will be created.
     * @param shoppingCartFactory A factory from which any
     *                            {@link model::ShoppingCart} instances
     *                            will be created.
     */
    TerminalView(
            controller::SaleControllerBuilder& saleControllerBuilder,
            model::ShoppingCartFactory& shoppingCartFactory)
        : saleControllerBuilder(saleControllerBuilder)
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
