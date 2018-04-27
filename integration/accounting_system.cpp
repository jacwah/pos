#include "integration/accounting_system.h"
#include <iostream>

namespace integration {

void AccountingSystem::handleSaleEvent(const SaleEvent& saleEvent)
{
    std::cout
        << "Sending sale information ("
        << saleEvent.getNetPrice()
        << ") to external accounting system..."
        << std::endl;
}

}
