#pragma once

#include "integration/dto.h"
#include "util/percentage.h"
#include "util/amount.h"

namespace model {

class Discount {
    util::Percentage percentage;

    public:
    Discount() : percentage(0) {}
    Discount(util::Percentage percentage) : percentage(percentage) {}

    util::Amount applyTo(util::Amount amount) const
    {
        return percentage.deductFrom(amount);
    }
};

}
