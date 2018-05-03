#include "integration/accounting_system.h"

namespace integration {

void AccountingSystem::handleSaleEvent(const SaleEvent& saleEvent)
{
    stream
        << "Sending sale information ("
        << saleEvent.getNetPrice()
        << ") to external accounting system..."
        << std::endl;
}

}
