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
    util::Amount discountAmount;
    util::Amount grossPrice;
    util::Amount totalTax;

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
            logSale(saleLog, payedAmount, netPrice, change);

            return change;
        }
    }

    util::Amount calculateNetPrice()
    {
        grossPrice = shoppingCart.calculateGrossPrice();
        discountAmount = discount.getAmount(grossPrice);
        util::Amount discountedPrice = grossPrice - discountAmount;
        totalTax = SALES_TAX.applyTo(discountedPrice);
        util::Amount netPrice = discountedPrice + totalTax;

        return netPrice;
    }

    void setDiscount(Discount discount)
    {
        this->discount = discount;
    }

private:
    void logSale(
            SaleLog& saleLog,
            util::Amount payedAmount,
            util::Amount netPrice,
            util::Amount changeAmount)
    {
        std::vector<integration::SoldItemRecord> soldItems;

        integration::SaleEvent saleEvent(
                soldItems,
                discountAmount,
                grossPrice,
                totalTax,
                netPrice,
                payedAmount,
                changeAmount);

        saleLog.append(saleEvent);
    }
};

}
