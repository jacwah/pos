#pragma once

#include "integration/dto.h"
#include "util/amount.h"
#include "util/optional.h"

namespace model {

/**
 * Represents a summary of state of a {@link model::ShoppingCart}.
 */
class ShoppingCartSummary {
    integration::Item lastAddedItem;
    util::Amount grossPrice;

public:
    /**
     * Creates a new instance.
     *
     * @param item The item last added to the shopping cart.
     * @param grossPrice The gross price of all items in the shopping cart.
     */
    ShoppingCartSummary(integration::Item item, util::Amount grossPrice)
        : lastAddedItem(item)
        , grossPrice(grossPrice)
    {}

    /**
     * Gets the last added item.
     *
     * @return The last added item.
     */
    const integration::Item getLastAddedItem() const
    {
        return lastAddedItem;
    }

    /**
     * Gets the gross price.
     *
     * @return The gross price of all items in the shopping cart.
     */
    const util::Amount getGrossPrice() const
    {
        return grossPrice;
    }
};

}
