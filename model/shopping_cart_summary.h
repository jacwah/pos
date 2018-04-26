#pragma once

#include "integration/dto.h"
#include "util/amount.h"
#include "util/optional.h"

namespace model {

class ShoppingCartSummary {
    util::optional<integration::Item> lastAddedItem;
    util::Amount grossPrice;

public:
    ShoppingCartSummary()
        : lastAddedItem()
        , grossPrice(0)
    {}

    ShoppingCartSummary(util::optional<integration::Item> item, util::Amount grossPrice)
        : lastAddedItem(item)
        , grossPrice(grossPrice)
    {}

    ShoppingCartSummary(const ShoppingCartSummary& other)
        : grossPrice(other.grossPrice)
        , lastAddedItem(other.lastAddedItem)
    {}

    const util::optional<integration::Item> getLastAddedItem() const
    {
        return lastAddedItem;
    }

    const util::Amount getGrossPrice() const
    {
        return grossPrice;
    }
};

}

std::ostream& operator<<(std::ostream& os, const model::ShoppingCartSummary& summary)
{
    os << "LastAdded=";

    auto item = summary.getLastAddedItem();
    if (item)
        os << *item;
    else
        os << "(None)";

    os << " GrossPrice=" << summary.getGrossPrice();

    return os;
}
