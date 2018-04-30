#include "integration/inventory_system.h"
#include <iostream>

namespace integration {

void InventorySystem::handleSaleEvent(const SaleEvent& saleEvent)
{
    std::cout
        << "Sending sale information ("
        << saleEvent.getItems().size()
        << " items) to external inventory system..."
        << std::endl;
}

}
