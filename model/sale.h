#pragma once

#include "model/shopping_cart.h"
#include "model/sale_log.h"
#include "util/optional.h"
#include "util/amount.h"

namespace model {

const util::Percentage SALES_TAX(0.25);

class Sale {
    std::vector<model::ItemRecord> items;

public:
    Sale(std::vector<model::ItemRecord> items)
        : items(items)
    {}

    util::optional<util::Amount> complete(util::Amount, SaleLog& saleLog)
    {
        return {};
    }

    util::Amount calculateNetPrice() const
    {
        util::Amount netPrice;

        for (auto& record : items)
            netPrice += SALES_TAX.addTo(record.item.getPrice() * record.quantity);

        return netPrice;
    }
};

}
