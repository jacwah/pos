#pragma once

#include <experimental/optional>

namespace integration {

class CustomerCatalog {
public:
    std::experimental::optional<Customer> find(CustomerId id) const
    {
        switch (id) {
            case 1: return Customer("Jacob", 0.5);
            case 2: return Customer("Linus", 0.25);
            default: return {};
        }
    }
};

}
