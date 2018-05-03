#pragma once

#include "integration/sale_log_observer.h"

namespace integration {

/**
 * Represents a connected receipt printer.
 */
class ReceiptPrinter : public SaleLogObserver {
    /**
     * Print a receipt.
     *
     * @param event Contains information about a completed sale.
     */
    virtual void handleSaleEvent(const SaleEvent& event);
};

}
