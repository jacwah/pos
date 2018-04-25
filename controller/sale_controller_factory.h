#pragma once

#include "controller/sale_controller.h"
#include "model/sale_log.h"
#include "model/discount_rules.h"

namespace controller {

class SaleControllerFactory {
    model::DiscountRules& discountRules;
    model::SaleLog& saleLog;

public:
    SaleControllerFactory(model::DiscountRules& discountRules, model::SaleLog& saleLog)
        : discountRules(discountRules)
        , saleLog(saleLog)
    {}

    SaleController create(model::ShoppingCartSummary& shoppingCartSummary)
    {
        return { shoppingCartSummary, discountRules, saleLog };
    }
};

}
