#pragma once

#include "integration/item_catalog.h"
#include "integration/customer_catalog.h"

namespace integration {
class CatalogCreator {
    ItemCatalog itemCatalog;
    CustomerCatalog customerCatalog;

    public:
    CatalogCreator() : itemCatalog(), customerCatalog() {}
    ItemCatalog& getItemCatalog()
    {
        return itemCatalog;
    }

    const CustomerCatalog& getCustomerCatalog() const
    {
        return customerCatalog;
    }
};
}
