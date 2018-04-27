#pragma once

#include <iterator>
#include "integration/sale_log_observer.h"
#include "integration/receipt_printer.h"
#include "integration/accounting_system.h"
#include "integration/inventory_system.h"

namespace integration {

std::vector<std::unique_ptr<SaleLogObserver>> createSaleObservers()
{
    std::vector<std::unique_ptr<SaleLogObserver>> observers;

    observers.emplace_back(std::make_unique<RecieptPrinter>());
    observers.emplace_back(std::make_unique<InventorySystem>());
    observers.emplace_back(std::make_unique<AccountingSystem>());

    return observers;
}

}
