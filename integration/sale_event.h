#pragma once

#include "integration/dto.h"
#include "util/time.h"
#include <vector>

namespace integration {

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

    util::Time getTimestamp() const
    {
        return timestamp;
    }

    const std::vector<SoldItemRecord>& getItems() const
    {
        return soldItems;
    }

    util::Amount getDiscountAmount() const
    {
        return discountAmount;
    }

    util::Amount getGrossPrice() const
    {
        return grossPrice;
    }

    util::Amount getTotalTax() const
    {
        return totalTax;
    }
    util::Amount getNetPrice() const
    {
        return netPrice;
    }
    util::Amount getPayedAmount() const
    {
        return payedAmount;
    }
    util::Amount getChangeAmount() const
    {
        return changeAmount;
    }
};

}
