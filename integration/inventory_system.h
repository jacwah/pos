#pragma once

#include "sale_log_observer.h"

namespace integration {

class InventorySystem : public SaleLogObserver {
public:
    virtual void handleSaleEvent(const SaleEvent& saleEvent);
};

}
