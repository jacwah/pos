#pragma once

#include "integration/sale_log_observer.h"

namespace view {

/**
 * Shows the total revenue from all sales during the program's execution.
 */
class TotalRevenueView : public integration::SaleLogObserver {
    util::Amount totalRevenue;

public:
    virtual void handleSaleEvent(const integration::SaleEvent& saleEvent);
};

}
