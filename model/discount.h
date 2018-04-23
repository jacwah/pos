#pragma once

#include "integration/dto.h"

namespace model {

class Discount {
    integration::Percentage percentage;

    public:
    Discount() : percentage(0) {}
    Discount(integration::Percentage percentage) : percentage(percentage) {}

    integration::Amount applyTo(integration::Amount amount) const
    {
        return percentage.deductFrom(amount);
    }
};

}
