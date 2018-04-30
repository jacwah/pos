#pragma once

#include "integration/item_catalog.h"
#include "integration/customer_catalog.h"

namespace integration {

/**
 * Creates and stores catalogs.
 */
class CatalogCreator {
    ItemCatalog itemCatalog;
    CustomerCatalog customerCatalog;

public:
    /**
     * Creates a new instance.
     */
    CatalogCreator()
        : itemCatalog()
        , customerCatalog()
    {}

    /**
     * Gets the created {@link integration::ItemCatalog}.
     *
     * @return The created item catalog.
     */
    ItemCatalog& getItemCatalog()
    {
        return itemCatalog;
    }

    /**
     * Gets the created {@link integration::CustomerCatalog}.
     *
     * @return The created customer catalog.
     */
    const CustomerCatalog& getCustomerCatalog() const
    {
        return customerCatalog;
    }
};

}
