#pragma once

#include "model/shopping_cart.h"
#include "model/discount.h"
#include "model/sale_log.h"
#include "util/optional.h"
#include "util/amount.h"

namespace model {

// TODO: Create cpp file to hide SALES_TAX etc.
const util::Percentage SALES_TAX(0.25);

/**
 * Represents a sale in progress.
 */
class Sale {
    const ShoppingCart& shoppingCart;
    Discount discount;
    util::Amount discountAmount;
    util::Amount grossPrice;
    util::Amount totalTax;

public:
    /**
     * Creates a new instance.
     *
     * @param shoppingCart Contains the items to be sold.
     */
    Sale(const ShoppingCart& shoppingCart)
        : shoppingCart(shoppingCart)
        , discount()
    {}

    /**
     * Completes the sale, sending information to <code>saleLog</code>.
     *
     * @param payedAmount The amount the customer payed.
     * @param saleLog Where sale information is sent.
     * @return The amount of change to give the customer, or nothing if
     *         <code>payedAmount</code> is insufficient.
     */
    util::optional<util::Amount> complete(util::Amount payedAmount, SaleLog& saleLog)
    {
        util::Amount netPrice = calculateNetPrice();

        if (payedAmount < netPrice) {
            return {};
        } else {
            util::Amount change = payedAmount - netPrice;
            logSale(saleLog, payedAmount, netPrice, change);

            return change;
        }
    }

    /**
     * Calculates the net price.
     *
     * @return The net price.
     */
    util::Amount calculateNetPrice()
    {
        grossPrice = shoppingCart.calculateGrossPrice();
        discountAmount = discount.getAmount(grossPrice);
        util::Amount discountedPrice = grossPrice - discountAmount;
        totalTax = SALES_TAX.applyTo(discountedPrice);
        util::Amount netPrice = discountedPrice + totalTax;

        return netPrice;
    }

    /**
     * Sets the discount.
     *
     * @param discount The discount to apply.
     */
    void setDiscount(Discount discount)
    {
        this->discount = discount;
    }

private:
    void logSale(
            SaleLog& saleLog,
            util::Amount payedAmount,
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
                payedAmount,
                changeAmount);

        saleLog.append(saleEvent);
    }
};

}
