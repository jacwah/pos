#pragma once

#include "model/shopping_cart.h"
#include "model/sale_log.h"
#include "util/optional.h"
#include "util/amount.h"

namespace model {

const util::Percentage SALES_TAX(0.25);

class Sale {
    const model::ShoppingCart& shoppingCart;

public:
    Sale(const model::ShoppingCart& shoppingCart)
        : shoppingCart(shoppingCart)
    {}

    util::optional<util::Amount> complete(util::Amount payedAmount, SaleLog& saleLog)
    {
        util::Amount netPrice = calculateNetPrice();

        if (payedAmount < netPrice) {
            return {};
        } else {
            util::Amount change = payedAmount - netPrice;
            saleLog.append({0});

            return change;
        }
    }

    util::Amount calculateNetPrice() const
    {
        util::Amount grossPrice = shoppingCart.calculateGrossPrice();
        util::Amount netPrice = SALES_TAX.addTo(grossPrice);

        return netPrice;
    }
};

}
