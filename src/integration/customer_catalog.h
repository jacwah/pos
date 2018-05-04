#pragma once

#include "integration/dto.h"
#include "util/optional.h"

namespace integration {

/**
 * A class for retrieving information about customers from a database.
 */
class CustomerCatalog {
public:
    /**
     * Searches for a customer in the database.
     *
     * @param id An identifier for the searched customer.
     * @return A {@link intergration::Customer} instance representing the found
     *         customer, or nothing if not found.
     */
    util::optional<Customer> find(CustomerId id) const
    {
        switch (id) {
            case 1: return Customer("Jacob", 0.5);
            case 2: return Customer("Linus", 0.25);
            default: return {};
        }
    }
};

}
