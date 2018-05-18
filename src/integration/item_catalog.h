#pragma once

#include "integration/dto.h"
#include "util/optional.h"

namespace integration {

class InvalidItemIdException : public std::exception {
    ItemId id;
    std::string message;

public:
    InvalidItemIdException(ItemId id)
        : id(id)
        , message("Could not find item ")
    {
        message.append(std::to_string(id));
    }

    const char *what() const throw()
    {
        return message.c_str();
    }
};

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
     * @return A description of the sought item.
     * @throws InvalidItemIdException If the requested item cannot be found.
     */
    Item find(ItemId id)
    {
        switch (id) {
            case 1: return Item("Milk", 1);
            case 2: return Item("Bread", 2);
            default: throw InvalidItemIdException(id);
        }
    }
};

}
