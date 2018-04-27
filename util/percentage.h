#pragma once

#include <cassert>
#include "util/amount.h"

namespace util {

class Percentage {
    double value;

    public:
    Percentage(double value) : value(value)
    {
        assert(0.0 <= value);
        assert(value <= 1.0);
    }

    util::Amount deductFrom(util::Amount amount) const
    {
        return amount * (1 - value);
    }

    util::Amount addTo(util::Amount amount) const
    {
        return amount * (1 + value);
    }

    util::Amount applyTo(util::Amount amount) const
    {
        return amount * value;
    }

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

