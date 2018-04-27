#pragma once

#include "controller/sale_controller_factory.h"
#include "model/shopping_cart_factory.h"
#include "util/optional.h"

namespace view {

struct ItemIdRecord {
    integration::ItemId itemId;
    int quantity;

    ItemIdRecord(integration::ItemId itemId, int quantity) : itemId(itemId), quantity(quantity) {}
};

class TerminalView {
    controller::SaleControllerFactory saleControllerFactory;
    model::ShoppingCartFactory shoppingCartFactory;

public:
    TerminalView(
            controller::SaleControllerFactory saleControllerFactory,
            model::ShoppingCartFactory shoppingCartFactory)
        : saleControllerFactory(saleControllerFactory)
        , shoppingCartFactory(shoppingCartFactory)
    {}

    void runLoop();
    void runSingle();

private:
    util::optional<int> getAndParseInt() const;
    util::optional<int> parseInt(const std::string& string) const;
    util::optional<ItemIdRecord> parseItemEnter(const std::string& line) const;
};

}
