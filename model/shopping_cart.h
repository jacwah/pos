#pragma once

#include <unordered_map>
#include "model/shopping_cart_summary.h"
#include "integration/dto.h"
#include "integration/item_catalog.h"

namespace model {

struct ItemRecord {
    integration::Item item;
    int quantity;

    ItemRecord(integration::Item item, int quantity)
        : item(item)
        , quantity(quantity)
    {}
};

class ShoppingCart {
    std::unordered_map<integration::ItemId, ItemRecord> items;
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
                iterator->second.quantity += 1;
            }
        }

        return ShoppingCartSummary(item, calculateGrossPrice());
    }

private:
    util::Amount calculateGrossPrice()
    {
        util::Amount sum = 0;

        for (auto keyvalue : items) {
            auto record = keyvalue.second;

            sum += record.item.getPrice() * record.quantity;
        }

        return sum;
    }
};

}

