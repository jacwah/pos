#pragma once

#include "util/amount.h"

namespace util {

/**
 * Represents a percentage.
 */
class Percentage {
    double value;

public:
    /**
     * Creates a new instance.
     *
     * @param The ratio.
     */
    Percentage(double value) 
        : value(value)
    {}

    /**
     * Deducts the percentage from an amount.
     *
     * @param amount The amount to deduct from.
     * @return The deducted amount.
     */
    util::Amount deductFrom(util::Amount amount) const
    {
        return amount * (1 - value);
    }

    /**
     * Adds the percentage to an amount.
     *
     * @param amount The amount to be added to.
     * @return The sum.
     */
    util::Amount addTo(util::Amount amount) const
    {
        return amount * (1 + value);
    }

    /**
     * Applies the percentage to an amount.
     *
     * @param amount The amount the percentage will be applied to.
     * @return The resulting amount.
     */
    util::Amount applyTo(util::Amount amount) const
    {
        return amount * value;
    }

    /**
     * Converts to a scalar.
     *
     * @return The ratio.
     */
    explicit operator double() const
    {
        return value;
    }
};

}

inline std::ostream& operator<<(std::ostream& os, const util::Percentage& percentage)
{
    os << static_cast<double>(percentage) << "%";
    return os;
}

