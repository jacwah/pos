#pragma once

#include "integration/sale_event.h"

namespace integration {

/**
 * Interface for classes that observe completed sales.
 */
class SaleLogObserver {
public:
    /**
     * Handles the completed sale in an implementation specific way.
     *
     * @param saleEvent Information about a completed sale.
     */
    virtual void handleSaleEvent(const SaleEvent& saleEvent) = 0;
};

}

