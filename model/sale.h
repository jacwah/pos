#pragma once

#include "model/shopping_cart.h"
#include "model/discount.h"
#include "model/sale_log.h"
#include "util/optional.h"
#include "util/amount.h"

namespace model {

/**
 * Represents a sale in progress.
 */
class Sale {
    const ShoppingCart& shoppingCart;
    Discount discount;
    util::Amount discountAmount;
    util::Amount grossPrice;
    util::Amount totalTax;

public:
    /**
     * Creates a new instance.
     *
     * @param shoppingCart Contains the items to be sold.
     */
    Sale(const ShoppingCart& shoppingCart)
        : shoppingCart(shoppingCart)
        , discount()
    {}

    /**
     * Completes the sale, sending information to <code>saleLog</code>.
     *
     * @param payedAmount The amount the customer payed.
     * @param saleLog Where sale information is sent.
     * @return The amount of change to give the customer, or nothing if
     *         <code>payedAmount</code> is insufficient.
     */
    util::optional<util::Amount> complete(util::Amount payedAmount, SaleLog& saleLog);

    /**
     * Calculates the net price.
     *
     * @return The net price.
     */
    util::Amount calculateNetPrice();

    /**
     * Sets the discount.
     *
     * @param discount The discount to apply.
     */
    void setDiscount(Discount discount)
    {
        this->discount = discount;
    }

private:
    void logSale(
            SaleLog& saleLog,
            util::Amount payedAmount,
            util::Amount netPrice,
            util::Amount changeAmount);
};

}
