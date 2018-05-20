#pragma once

#include "controller/sale_controller.h"
#include "model/shopping_cart.h"
#include "model/sale_log.h"
#include "model/discount_rules.h"

namespace controller {

/**
 * A builder class for creating {@link controller::SaleControllerFactory}
 * instances.
 */
class SaleControllerBuilder {
    std::shared_ptr<model::DiscountRules> discountRules;
    std::shared_ptr<model::SaleLog> saleLog;

public:
    /**
     * Creates a new instance.
     *
     * @param discountRules The rules that should govern discounts in all sales
     *                      handled by controllers created with this instance.
     */
    SaleControllerBuilder(
            std::shared_ptr<model::DiscountRules> discountRules)
        : discountRules(discountRules)
    {
        saleLog = std::make_shared<model::SaleLog>();
    }

    /**
     * Sets the {@link model::SaleLog} to use for new controllers created by
     * this object.
     *
     * @param saleLog The log where sales completed by controllers created with
     *                this instance should be recorded.
     */
    void setSaleLog(std::shared_ptr<model::SaleLog> saleLog)
    {
        this->saleLog = saleLog;
    }

    /**
     * Creates a new {@link controller::SaleController} instance.
     *
     * @param shoppingCart An object containing the items to be sold.
     */
    SaleController build(const model::ShoppingCart& shoppingCart)
    {
        return {shoppingCart, discountRules, saleLog};
    }
};

}
