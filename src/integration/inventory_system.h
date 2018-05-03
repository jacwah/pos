#pragma once

#include "sale_log_observer.h"
#include <iostream>

namespace integration {

/**
 * Represents the external inventory system. Used to send information about
 * completed sales.
 */
class InventorySystem : public SaleLogObserver {
    std::ostream& stream;

public:
    /**
     * Creates a new instance.
     *
     * @param stream The stream to write output to.
     */
    InventorySystem(std::ostream& stream)
        : stream(stream)
    {}

    /**
     * Sends information about a completed sale to the inventory system.
     *
     * @param saleEvent The available information.
     */
    virtual void handleSaleEvent(const SaleEvent& saleEvent);
};

}
