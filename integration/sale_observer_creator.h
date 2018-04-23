#pragma once

#include <iterator>
#include "integration/sale_log_observer.h"
#include "integration/receipt_printer.h"

namespace integration {

std::vector<std::shared_ptr<SaleLogObserver>> createSaleObservers()
{
    std::vector<std::shared_ptr<SaleLogObserver>> observers;

    observers.push_back(std::make_shared<RecieptPrinter>());

    return observers;
}

}
