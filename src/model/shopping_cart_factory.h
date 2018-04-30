#pragma once

#include "model/shopping_cart.h"
#include "integration/catalog_creator.h"

namespace model {

/**
 * Creates {@link model::ShoppingCart}s.
 */
class ShoppingCartFactory {
    integration::ItemCatalog& itemCatalog;

public:
    /**
     * Creates a new instance.
     *
     * @param catalogCreator Contains the catalogs to be used by
     *                       {@link model::ShoppingCart}s created by this
     *                       instance.
     */
    ShoppingCartFactory(integration::CatalogCreator& catalogCreator)
        : itemCatalog(catalogCreator.getItemCatalog()) {}

    /**
     * Creates a new {@link model::ShoppingCart}.
     *
     * @return A new shopping cart.
     */
    ShoppingCart createCart() const
    {
        return ShoppingCart(itemCatalog);
    }
};

}
