#pragma once

#include "integration/dto.h"
#include "util/optional.h"

namespace integration {

/**
 * An exception indicating that a requested item could not be found.
 */
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
 * An exception thrown when a database error occurrs.
 */
class DatabaseErrorException : public std::exception {
public:
    const char *what() const throw()
    {
        return "A database error occurred";
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
     * @throws DatabaseErrorException If there was an error with the underlying
     *                                database.
     */
    Item find(ItemId id)
    {
        switch (id) {
            case 1: return Item("Milk", 1);
            case 2: return Item("Bread", 2);
            case 666: throw DatabaseErrorException();
            default: throw InvalidItemIdException(id);
        }
    }
};

}
