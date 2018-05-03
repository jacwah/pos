#include "integration/inventory_system.h"

namespace integration {

void InventorySystem::handleSaleEvent(const SaleEvent& saleEvent)
{
    stream
        << "Sending sale information ("
        << saleEvent.getItems().size()
        << " items) to external inventory system..."
        << std::endl;
}

}
