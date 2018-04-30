#pragma once

#include "sale_log_observer.h"

namespace integration {

/**
 * Represents the external inventory system. Used to send information about
 * completed sales.
 */
class InventorySystem : public SaleLogObserver {
public:
    /**
     * Sends information about a completed sale to the inventory system.
     *
     * @param saleEvent The available information.
     */
    virtual void handleSaleEvent(const SaleEvent& saleEvent);
};

}
