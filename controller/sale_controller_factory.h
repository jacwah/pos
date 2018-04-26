#pragma once

#include "controller/sale_controller.h"
#include "model/shopping_cart.h"
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

    SaleController create(model::ShoppingCart& shoppingCart)
    {
        std::vector<model::ItemRecord> items;

        for (auto& id_item : shoppingCart)
            items.push_back(id_item.second);

        return {items, discountRules, saleLog};
    }
};

}
