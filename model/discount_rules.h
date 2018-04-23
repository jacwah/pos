#pragma once

#include "model/discount.h"
#include "integration/customer_catalog.h"
#include "integration/catalog_creator.h"

namespace model {

class DiscountRules {
    const integration::CustomerCatalog customerCatalog;

    public:
    DiscountRules(const integration::CatalogCreator catalogCreator)
        : customerCatalog(catalogCreator.getCustomerCatalog()) {}

    model::Discount getDiscountFor(integration::CustomerId customerId) const
    {
        if (auto customer = customerCatalog.find(customerId))
            return {customer->getDiscountPercentage()};
        else
            return {};
    }
};

}
