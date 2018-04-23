#pragma once

#include <iterator>
#include "integration/sale_log_observer.h"
#include "integration/receipt_printer.h"

namespace integration {

std::vector<std::unique_ptr<SaleLogObserver>> createSaleObservers()
{
    std::vector<std::unique_ptr<SaleLogObserver>> observers;

    observers.push_back(std::make_unique<RecieptPrinter>());

    return observers;
}

}
