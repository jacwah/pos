#pragma once

#include <unordered_map>
#include "model/shopping_cart_summary.h"
#include "integration/dto.h"
#include "integration/item_catalog.h"

namespace model {

class ItemRecord {
    integration::Item item;
    int quantity;

public:
    ItemRecord(integration::Item item, int quantity)
        : item(item)
        , quantity(quantity)
    {}

    const integration::Item& getItem() const
    {
        return item;
    }

    int getQuantity() const
    {
        return quantity;
    }

    void incrementQuantity()
    {
        ++quantity;
    }
};

typedef std::unordered_map<integration::ItemId, ItemRecord> ItemMap;

class ShoppingCart {
    ItemMap items;
    integration::ItemCatalog& itemCatalog;

public:
    ShoppingCart(integration::ItemCatalog& itemCatalog) : itemCatalog(itemCatalog) {}

    ShoppingCart& operator=(const ShoppingCart& other)
    {
        if (this != &other) {
            items = other.items;
            itemCatalog = other.itemCatalog;
        }
        return *this;
    }

    ShoppingCartSummary addIfValid(integration::ItemId id, int quantity)
    {
        auto item = itemCatalog.find(id);

        if (item) {
            auto iterator = items.find(id);

            if (iterator == items.end()) {
                ItemRecord record(*item, quantity);
                items.emplace(std::make_pair(id, record));
            } else {
                iterator->second.incrementQuantity();
            }
        }

        return ShoppingCartSummary(item, calculateGrossPrice());
    }

    ItemMap::const_iterator begin() const
    {
        return items.cbegin();
    }

    ItemMap::const_iterator end() const
    {
        return items.cend();
    }

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

