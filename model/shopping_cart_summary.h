#pragma once

#include <experimental/optional>
#include "integration/dto.h"

namespace model {

class ShoppingCartSummary {
    const std::experimental::optional<integration::Item> lastAddedItem;
    const integration::Amount grossPrice;

    public:
    ShoppingCartSummary(std::experimental::optional<integration::Item> item, integration::Amount grossPrice)
        : lastAddedItem(item)
        , grossPrice(grossPrice)
    {}

    const std::experimental::optional<integration::Item> getLastAddedItem() const
    {
        return lastAddedItem;
    }

    const integration::Amount getGrossPrice() const
    {
        return grossPrice;
    }
};

}
