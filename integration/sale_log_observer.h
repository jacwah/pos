#pragma once

#include "integration/dto.h"

namespace integration {

class SaleLogObserver {
    public:
    virtual void handleSaleEvent(const SaleEvent&) = 0;
};

}

