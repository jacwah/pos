#pragma once

#include "sale_log_observer.h"

namespace integration {

/**
 * Represents the external accounting system. Used to send information about
 * completed sales.
 */
class AccountingSystem : public SaleLogObserver {
public:
    /**
     * Sends information about a completed sale to the external accounting
     * system.
     *
     * @param saleEvent Describes a completed sale.
     */
    virtual void handleSaleEvent(const SaleEvent& saleEvent);
};

}
