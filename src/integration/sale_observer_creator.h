#pragma once

#include "integration/sale_log_observer.h"
#include "integration/receipt_printer.h"
#include "integration/accounting_system.h"
#include "integration/inventory_system.h"

namespace integration {

/**
 * Creates a list of all {@link integration::SaleLogObserver}s to be notified
 * of competed sales.
 *
 * @return A list of observers that should be notified.
 */
std::vector<std::unique_ptr<SaleLogObserver>> createSaleObservers()
{
    std::vector<std::unique_ptr<SaleLogObserver>> observers;

    observers.emplace_back(std::make_unique<ReceiptPrinter>());
    observers.emplace_back(std::make_unique<InventorySystem>());
    observers.emplace_back(std::make_unique<AccountingSystem>());

    return observers;
}

}
