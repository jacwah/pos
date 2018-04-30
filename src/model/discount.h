#pragma once

#include "integration/dto.h"
#include "util/percentage.h"
#include "util/amount.h"

namespace model {

/**
 * Represents a sale discount.
 */
class Discount {
    util::Percentage percentage;

public:
    /**
     * Creates a default instance with no discount.
     */
    Discount()
        : percentage(0)
    {}

    /**
     * Creates a new instance.
     *
     * @param percentage The percentage discount to be used.
     */
    Discount(util::Percentage percentage)
        : percentage(percentage)
    {}

    /**
     * Apply the discount to an amount.
     *
     * @param amount The amount to apply to.
     * @return The amount after applying the discount.
     */
    util::Amount applyTo(util::Amount amount) const
    {
        return percentage.deductFrom(amount);
    }

    /**
     * Get the discount amount for a given amount.
     *
     * @param amountToBeDiscounted The amount to be discounted.
     * @return The amount of discount given <code>amountToBeDiscounted</code>.
     */
    util::Amount getAmount(util::Amount amountToBeDiscounted) const
    {
        return percentage.applyTo(amountToBeDiscounted);
    }
};

}
