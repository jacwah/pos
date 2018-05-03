#pragma once

#include "sale_log_observer.h"
#include <iostream>

namespace integration {

/**
 * Represents the external accounting system. Used to send information about
 * completed sales.
 */
class AccountingSystem : public SaleLogObserver {
    std::ostream& stream;

public:
    /**
     * Creates a new instance.
     *
     * @param stream The stream to write output to.
     */
    AccountingSystem(std::ostream& stream)
        : stream(stream)
    {}

    /**
     * Sends information about a completed sale to the external accounting
     * system.
     *
     * @param saleEvent Describes a completed sale.
     */
    virtual void handleSaleEvent(const SaleEvent& saleEvent);
};

}
