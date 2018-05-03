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
    util::Amount paidAmount;
    util::Amount changeAmount;

public:
    /**
     * Creates a new instance.
     *
     * @param soldItems The items and quantities sold in the sale.
     * @param discountAmount The discount given to the customer.
     * @param grossPrice The gross price of the <code>soldItems</code>.
     * @param totalTax The total sales tax paid.
     * @param netPrice The net price of the sale.
     * @param paidAmount The amount the customer paid.
     * @param changeAmount The amount of change given back to the customer.
     */
    SaleEvent(
            std::vector<SoldItemRecord> soldItems,
            util::Amount discountAmount,
            util::Amount grossPrice,
            util::Amount totalTax,
            util::Amount netPrice,
            util::Amount paidAmount,
            util::Amount changeAmount)
        : timestamp()
        , soldItems(soldItems)
        , discountAmount(discountAmount)
        , grossPrice(grossPrice)
        , totalTax(totalTax)
        , netPrice(netPrice)
        , paidAmount(paidAmount)
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
     * Gets the total sales tax paid.
     *
     * @return The total sales tax paid.
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
     * Gets the amount paid by the customer.
     *
     * @return The amount paid by the customer.
     */
    util::Amount getpaidAmount() const
    {
        return paidAmount;
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
