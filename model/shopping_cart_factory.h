#pragma once

#include "model/shopping_cart.h"
#include "integration/catalog_creator.h"

namespace model {

class ShoppingCartFactory {
    integration::ItemCatalog& itemCatalog;

    public:
    ShoppingCartFactory(integration::CatalogCreator& catalogCreator)
        : itemCatalog(catalogCreator.getItemCatalog()) {}
    
    ShoppingCart createCart() const
    {
        return ShoppingCart(itemCatalog);
    }
};

}
