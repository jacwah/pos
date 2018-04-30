#pragma once

#include "model/discount.h"
#include "integration/customer_catalog.h"
#include "integration/catalog_creator.h"

namespace model {

/**
 * Represents the rules governing sale discounts.
 */
class DiscountRules {
    const integration::CustomerCatalog customerCatalog;

public:
    /**
     * Creates a new instance.
     *
     * @param catalogCreator An object containing required catalogs.
     */
    DiscountRules(const integration::CatalogCreator catalogCreator)
        : customerCatalog(catalogCreator.getCustomerCatalog()) 
    {}

    /**
     * Gets the {@link model::Discount} for a given customer.
     *
     * @param customerId Identifies the customer.
     * @return The discount offered to the given customer.
     */
    Discount getDiscountFor(integration::CustomerId customerId) const
    {
        if (auto customer = customerCatalog.find(customerId))
            return {customer->getDiscountPercentage()};
        else
            return {};
    }
};

}
