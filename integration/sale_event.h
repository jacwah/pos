#pragma once

#include "integration/dto.h"
#include "util/time.h"
#include <vector>

namespace integration {

/**
 * Represents a completed sale.
 */
class SaleEvent {
    util::Time timestamp;
    std::vector<SoldItemRecord> soldItems;
    util::Amount discountAmount;
    util::Amount grossPrice;
    util::Amount totalTax;
    util::Amount netPrice;
    util::Amount payedAmount;
    util::Amount changeAmount;

public:
    /**
     * Creates a new instance.
     *
     * @param soldItems The items and quantities sold in the sale.
     * @param discountAmount The discount given to the customer.
     * @param grossPrice The gross price of the <code>soldItems</code>.
     * @param totalTax The total sales tax payed.
     * @param netPrice The net price of the sale.
     * @param payedAmount The amount the customer payed.
     * @param changeAmount The amount of change given back to the customer.
     */
    SaleEvent(
            std::vector<SoldItemRecord> soldItems,
            util::Amount discountAmount,
            util::Amount grossPrice,
            util::Amount totalTax,
            util::Amount netPrice,
            util::Amount payedAmount,
            util::Amount changeAmount)
        : timestamp()
        , soldItems(soldItems)
        , discountAmount(discountAmount)
        , grossPrice(grossPrice)
        , totalTax(totalTax)
        , netPrice(netPrice)
        , payedAmount(payedAmount)
        , changeAmount(changeAmount)
    {}

    /**
     * Gets the time the sale was completed.
     *
     * @return The time the sale was completed.
     */
    util::Time getTimestamp() const
    {
        return timestamp;
    }

    /**
     * Gets the items sold.
     *
     * @return The sold items.
     */
    const std::vector<SoldItemRecord>& getItems() const
    {
        return soldItems;
    }

    /**
     * Gets the discount given to the customer.
     *
     * @return The discount given to the customer.
     */
    util::Amount getDiscountAmount() const
    {
        return discountAmount;
    }

    /**
     * Gets the gross price of the sold items.
     *
     * @return The gross price of the sold items.
     */
    util::Amount getGrossPrice() const
    {
        return grossPrice;
    }

    /**
     * Gets the total sales tax payed.
     *
     * @return The total sales tax payed.
     */
    util::Amount getTotalTax() const
    {
        return totalTax;
    }

    /**
     * Gets the net price of the sale.
     *
     * @return The net price.
     */
    util::Amount getNetPrice() const
    {
        return netPrice;
    }

    /**
     * Gets the amount payed by the customer.
     *
     * @return The amount payed by the customer.
     */
    util::Amount getPayedAmount() const
    {
        return payedAmount;
    }

    /**
     * Gets the amount of change given to the customer.
     *
     * @return The amount of change given to the customer.
     */
    util::Amount getChangeAmount() const
    {
        return changeAmount;
    }
};

}
