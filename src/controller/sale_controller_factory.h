#pragma once

#include "controller/sale_controller.h"
#include "model/shopping_cart.h"
#include "model/sale_log.h"
#include "model/discount_rules.h"

namespace controller {

/**
 * A factory class for creating {@link controller::SaleControllerFactory}
 * instances.
 */
class SaleControllerFactory {
    model::DiscountRules& discountRules;
    model::SaleLog& saleLog;

public:
    /**
     * Creates a new instance.
     *
     * @param discountRules The rules that should govern discounts in all sales
     *                      handled by controllers created with this instance.
     * @param saleLog The log where sales completed by controllers created with
     *                this instance should be recorded.
     */
    SaleControllerFactory(
            model::DiscountRules& discountRules,
            model::SaleLog& saleLog)
        : discountRules(discountRules)
        , saleLog(saleLog)
    {}

    /**
     * Creates a new {@link controller::SaleController} instance.
     *
     * @param shoppingCart An object containing the items to be sold.
     */
    SaleController create(const model::ShoppingCart& shoppingCart)
    {
        return {shoppingCart, discountRules, saleLog};
    }
};

}
