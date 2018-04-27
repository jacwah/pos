#pragma once

#include "integration/sale_event.h"

namespace integration {

class SaleLogObserver {
    public:
    virtual void handleSaleEvent(const SaleEvent&) = 0;
};

}

