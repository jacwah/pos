#pragma once

#include <vector>
#include "model/shopping_cart_summary.h"
#include "integration/dto.h"
#include "integration/item_catalog.h"

namespace model {

class ShoppingCart {
    // TODO: hasmap or something
    std::vector<integration::Item> items;
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

        if (item)
            items.push_back(*item);

        return ShoppingCartSummary(item, util::Amount(0));
    }
};

}

