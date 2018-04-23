#pragma once

#include <experimental/optional>
#include "integration/dto.h"

namespace integration {

class ItemCatalog {
    public:
    std::experimental::optional<Item> find(ItemId id)
    {
        switch (id) {
            case 1: return Item("Milk", 1);
            case 2: return Item("Bread", 2);
            default: return {};
        }
    }
};

}
