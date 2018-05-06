#pragma once

#include <iostream>

namespace util {

/**
 * Represents a monetary amount. Is non-negative.
 */
class Amount {
    double value;

public:
    /**
     * Creates a new instance representing no money.
     */
    Amount()
        : value(0)
    {}

    /**
     * Creates a new instance.
     *
     * @param value The monetary amount.
     */
    Amount(double value)
        : value(value)
    {}

    /**
     * Compares the amount to another amount.
     *
     * @param other Amount to compare to.
     * @return <code>true</code> if this amount is less than <code>other</code>.
     */
    bool operator<(Amount other) const
    {
        return value < other.value;
    }

    /**
     * Compares the amount to another amount.
     *
     * @param other Amount to compare to.
     * @return <code>true</code> if this amount is exactly equal to <code>other</code>.
     */
    bool operator==(Amount other) const
    {
        return value == other.value;
    }

    /**
     * Multiplies the amount by a scalar.
     *
     * @param scalar The factor.
     * @return The product.
     */
    Amount operator*(double scalar) const
    {
        return value * scalar;
    }

    /**
     * Adds the amount to another amount.
     *
     * @param other The term.
     * @return The sum.
     */
    Amount operator+(Amount other) const
    {
        return value + other.value;
    }

    /**
     * Subtracts another amount.
     *
     * @param other The amount to subtract.
     * @return The difference.
     */
    Amount operator-(Amount other) const
    {
        return value - other.value;
    }

    /**
     * Adds and assigns the sum to this.
     *
     * @param other The term.
     * @return This.
     */
    Amount& operator+=(Amount other)
    {
        value += other.value;
        return *this;
    }

    /**
     * Converts to a scalar.
     *
     * @return The monetary amount as a scalar.
     */
    explicit operator double() const
    {
        return value;
    }
};

}

inline std::ostream& operator<<(std::ostream& os, const util::Amount& amount)
{
    os << "$" << static_cast<double>(amount);
    return os;
}
