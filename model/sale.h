#pragma once

#include "model/shopping_cart.h"
#include "model/discount.h"
#include "model/sale_log.h"
#include "util/optional.h"
#include "util/amount.h"

namespace model {

const util::Percentage SALES_TAX(0.25);

class Sale {
    const ShoppingCart& shoppingCart;
    Discount discount;

public:
    Sale(const ShoppingCart& shoppingCart)
        : shoppingCart(shoppingCart)
        , discount()
    {}

    util::optional<util::Amount> complete(util::Amount payedAmount, SaleLog& saleLog)
    {
        util::Amount netPrice = calculateNetPrice();

        if (payedAmount < netPrice) {
            return {};
        } else {
            util::Amount change = payedAmount - netPrice;
            saleLog.append({});

            return change;
        }
    }

    util::Amount calculateNetPrice() const
    {
        util::Amount grossPrice = shoppingCart.calculateGrossPrice();
        util::Amount taxedPrice = SALES_TAX.addTo(grossPrice);
        util::Amount netPrice = discount.applyTo(taxedPrice);

        return netPrice;
    }

    void setDiscount(Discount discount)
    {
        this->discount = discount;
    }
};

}
