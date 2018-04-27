#pragma once

#include "controller/sale_controller_factory.h"
#include "model/shopping_cart_factory.h"

namespace view {

class TerminalView {
    controller::SaleControllerFactory saleControllerFactory;
    model::ShoppingCartFactory shoppingCartFactory;

public:
    TerminalView(
            controller::SaleControllerFactory saleControllerFactory,
            model::ShoppingCartFactory shoppingCartFactory)
        : saleControllerFactory(saleControllerFactory)
        , shoppingCartFactory(shoppingCartFactory)
    {}

    void runLoop();
    void runSingle();
};

}
