#pragma once

#include "integration/sale_log_observer.h"
#include <iostream>

namespace integration {

/**
 * Represents a connected receipt printer.
 */
class ReceiptPrinter : public SaleLogObserver {
    std::ostream& stream;

public:
    /**
     * Creates a new instance.
     *
     * @param stream The stream to write output to.
     */
    ReceiptPrinter(std::ostream& stream)
        : stream(stream)
    {}

    /**
     * Print a receipt.
     *
     * @param event Contains information about a completed sale.
     */
    virtual void handleSaleEvent(const SaleEvent& event);
};

}
