#include "view/total_revenue_view.h"
#include <iostream>

namespace view {

void TotalRevenueView::handleSaleEvent(const integration::SaleEvent& saleEvent)
{
    totalRevenue += saleEvent.getNetPrice() - saleEvent.getTotalTax();
    std::cout << "Total revenue: " << totalRevenue << std::endl;
}

}
