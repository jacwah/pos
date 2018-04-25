#pragma once

#include "model/shopping_cart_summary.h"
#include "model/sale_log.h"
#include "util/optional.h"
#include "util/amount.h"

namespace model {

class Sale {

public:
    Sale(const ShoppingCartSummary& shoppingCartSummary)
    {}

    util::optional<util::Amount> complete(util::Amount, SaleLog& saleLog)
    {
        return {};
    }

    util::Amount calculateNetPrice()
    {
        return util::Amount(20);
    }
};

}
