#pragma once

#include <experimental/optional>
#include "util/amount.h"
#include "integration/dto.h"

namespace model {

class ShoppingCartSummary {
    const std::experimental::optional<integration::Item> lastAddedItem;
    const util::Amount grossPrice;

    public:
    ShoppingCartSummary(std::experimental::optional<integration::Item> item, util::Amount grossPrice)
        : lastAddedItem(item)
        , grossPrice(grossPrice)
    {}

    const std::experimental::optional<integration::Item> getLastAddedItem() const
    {
        return lastAddedItem;
    }

    const util::Amount getGrossPrice() const
    {
        return grossPrice;
    }
};

}
