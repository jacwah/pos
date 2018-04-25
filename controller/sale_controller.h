#pragma once

#include "model/discount_rules.h"
#include "model/sale_log.h"
#include "model/sale.h"
#include "model/shopping_cart_summary.h"
#include "model/discount_rules.h"
#include "integration/dto.h"
#include "util/amount.h"
#include "util/optional.h"

namespace controller {

class SaleController {
    model::DiscountRules& discountRules;
    model::SaleLog& saleLog;
    model::Sale sale;

public:
    SaleController(
            const model::ShoppingCartSummary& shoppingCartSummary,
            model::DiscountRules& discountRules,
            model::SaleLog& saleLog)
        : discountRules(discountRules)
        , saleLog(saleLog)
        , sale(shoppingCartSummary)
    {}

    util::Amount requestDiscount(integration::CustomerId customerId)
    {
        return util::Amount(0);
    }

    util::optional<util::Amount> payAndGetChange(util::Amount payedAmount)
    {
        return sale.complete(payedAmount, saleLog);
    }

    util::Amount getNetPrice()
    {
        return sale.calculateNetPrice();
    }
};

}
