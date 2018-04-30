#pragma once

#include "model/discount_rules.h"
#include "model/sale_log.h"
#include "model/sale.h"
#include "model/shopping_cart.h"
#include "model/discount.h"
#include "model/discount_rules.h"
#include "integration/dto.h"
#include "integration/sale_event.h"
#include "util/amount.h"
#include "util/optional.h"

namespace controller {

/**
 * Controller for mediating the fulfillment of a sale between views and the
 * model.
 */
class SaleController {
    model::DiscountRules& discountRules;
    model::SaleLog& saleLog;
    model::Sale sale;

public:
    /**
     * Creates a new instance.
     *
     * @param shoppingCart A shopping cart containing the items to be sold.
     * @param discountRules An object describing the rules for discounts in
     *                      this sale.
     * @param saleLog A place to log information about the sale when it is
     *                completed.
     */
    SaleController(
            const model::ShoppingCart& shoppingCart,
            model::DiscountRules& discountRules,
            model::SaleLog& saleLog)
        : discountRules(discountRules)
        , saleLog(saleLog)
        , sale(shoppingCart)
    {}

    /**
     * Requests a discount for the current sale based on the given customer.
     * If no discount is associated with the identifier, no discount is set.
     *
     * @param customerId An identifier for the customer the discount is
     *                   associated with.
     */
    void requestDiscount(integration::CustomerId customerId)
    {
        model::Discount discount = discountRules.getDiscountFor(customerId);
        sale.setDiscount(discount);
    }

    /**
     * Signals that the sale is payed for and should be considered completed.
     *
     * @param payedAmount The amount the customer has payed.
     * @return The amount of change the customer should recieve, or nothing if
     *         the <code>payedAmoount</code> is insufficient.
     */
    util::optional<util::Amount> payAndGetChange(util::Amount payedAmount)
    {
        return sale.complete(payedAmount, saleLog);
    }

    /**
     * Gives the net price of the sale in its current state.
     *
     * @return The net price.
     */
    util::Amount getNetPrice()
    {
        return sale.calculateNetPrice();
    }
};

}
