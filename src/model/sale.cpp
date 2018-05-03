#include "model/sale.h"

namespace model {

const util::Percentage SALES_TAX(0.25);

util::optional<util::Amount> Sale::complete(util::Amount paidAmount, SaleLog& saleLog)
{
    util::Amount netPrice = calculateNetPrice();

    if (paidAmount < netPrice) {
        return {};
    } else {
        util::Amount change = paidAmount - netPrice;
        logSale(saleLog, paidAmount, netPrice, change);

        return change;
    }
}

util::Amount Sale::calculateNetPrice()
{
    grossPrice = shoppingCart.calculateGrossPrice();
    discountAmount = discount.getAmount(grossPrice);
    util::Amount discountedPrice = grossPrice - discountAmount;
    totalTax = SALES_TAX.applyTo(discountedPrice);
    util::Amount netPrice = discountedPrice + totalTax;

    return netPrice;
}

void Sale::logSale(
        SaleLog& saleLog,
        util::Amount paidAmount,
        util::Amount netPrice,
        util::Amount changeAmount)
{
    std::vector<integration::SoldItemRecord> soldItems;
    for (auto& id_item : shoppingCart) {
        const integration::Item& item = id_item.second.getItem();
        int quantity = id_item.second.getQuantity();
        integration::SoldItemRecord soldItem(
                id_item.first,
                item,
                quantity,
                item.getPrice() * quantity);
        soldItems.push_back(soldItem);
    }

    std::sort(soldItems.begin(), soldItems.end());

    integration::SaleEvent saleEvent(
            soldItems,
            discountAmount,
            grossPrice,
            totalTax,
            netPrice,
            paidAmount,
            changeAmount);

    saleLog.append(saleEvent);
}

}
