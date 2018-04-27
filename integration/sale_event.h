#pragma once

#include "util/time.h"

namespace integration {

class SaleEvent {
    util::Time timestamp;

public:
    SaleEvent()
        : timestamp()
    {}

    util::Time getTimestamp() const
    {
        return timestamp;
    }
};

}
