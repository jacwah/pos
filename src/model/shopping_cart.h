#pragma once

#include <unordered_map>
#include "model/shopping_cart_summary.h"
#include "integration/dto.h"
#include "integration/item_catalog.h"

namespace model {

/**
 * Represents a set of items of the same type in a shopping cart.
 */
class ItemRecord {
    integration::Item item;
    int quantity;

public:
    /**
     * Create a new instance.
     *
     * @param item Describes the item.
     * @param quantity The number of items.
     */
    ItemRecord(integration::Item item, int quantity)
        : item(item)
        , quantity(quantity)
    {}

    /**
     * Gets the item.
     *
     * @return The item.
     */
    const integration::Item& getItem() const
    {
        return item;
    }

    /**
     * Gets the quantity.
     *
     * @return The quantity.
     */
    int getQuantity() const
    {
        return quantity;
    }

    /**
     * Increments the quantity.
     *
     * @param increment The amount to increment by.
     */
    void incrementQuantity(int increment)
    {
        quantity += increment;
    }
};

typedef std::unordered_map<integration::ItemId, ItemRecord> ItemMap;

/**
 * Contains items to be sold.
 */
class ShoppingCart {
    ItemMap items;
    integration::ItemCatalog& itemCatalog;

public:
    /**
     * Creates a new instance.
     *
     * @param itemCatalog A catalog of items that can be added to the cart.
     */
    ShoppingCart(integration::ItemCatalog& itemCatalog)
        : itemCatalog(itemCatalog)
    {}

    /**
     * Creates a new instance.
     *
     * @param other Another shopping cart to copy.
     */
    ShoppingCart& operator=(const ShoppingCart& other)
    {
        if (this != &other) {
            items = other.items;
            itemCatalog = other.itemCatalog;
        }
        return *this;
    }

    /**
     * Adds the identified item to the cart.
     *
     * @param id Identifies the item to be added.
     * @param quantity The number of the items to add.
     * @return A summary of the state of the shopping cart.
     * @throws InvalidItemId If <code>id</code> is invalid.
     */
    ShoppingCartSummary addItem(integration::ItemId id, int quantity)
    {
        auto item = itemCatalog.find(id);
        auto iterator = items.find(id);

        if (iterator == items.end()) {
            ItemRecord record(item, quantity);
            items.emplace(std::make_pair(id, record));
        } else {
            iterator->second.incrementQuantity(quantity);
        }

        return ShoppingCartSummary(item, calculateGrossPrice());
    }

    /**
     * Creates an iterator pointing to the first item record.
     *
     * @return An iterator.
     */
    ItemMap::const_iterator begin() const
    {
        return items.cbegin();
    }

    /**
     * Creates an iterator pointing to after the last item record.
     *
     * @return An iterator.
     */
    ItemMap::const_iterator end() const
    {
        return items.cend();
    }

    /**
     * Calculates the gross price of all items.
     *
     * @return The gross price.
     */
    util::Amount calculateGrossPrice() const
    {
        util::Amount sum = 0;

        for (auto id_item : items) {
            auto record = id_item.second;

            sum += record.getItem().getPrice() * record.getQuantity();
        }

        return sum;
    }
};

}

