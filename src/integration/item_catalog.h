#pragma once

#include "integration/dto.h"
#include "util/optional.h"

namespace integration {

/**
 * Holds the items that can be sold. Is used to interface with the external
 * database.
 */
class ItemCatalog {
public:
    /**
     * Searches for an item in the database.
     *
     * @param id Identifies the sought item.
     * @return A description of the sought item, or nothing if not found.
     */
    util::optional<Item> find(ItemId id)
    {
        switch (id) {
            case 1: return Item("Milk", 1);
            case 2: return Item("Bread", 2);
            default: return {};
        }
    }
};

}
