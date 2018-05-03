#include "integration/receipt_printer.h"
#include <iostream>
#include <iomanip>

namespace integration {

//TODO: STAVA receipt, paid
void RecieptPrinter::handleSaleEvent(const SaleEvent& event)
{
        std::cout
            << std::endl
            << "=== Receipt ===" << std::endl
            << "Time: " << event.getTimestamp() << std::endl
            << std::endl
            << "Id Item                Price" << std::endl
            << "----------------------------" << std::endl;

        for (auto& record : event.getItems()) {
            std::cout
                << std::setw(2) << std::setfill('0') << std::right << record.getItemId() << " ";
            std::cout
                << std::setw(20) << std::setfill(' ') << std::left << record.getItem().getDescription();
            std::cout
                << record.getTotalPrice() << std::endl;

            int quantity = record.getQuantity();
            if (quantity > 1)
                std::cout
                    << "    " << quantity << " x " << record.getItem().getPrice() << std::endl;
        }

        std::cout << std::endl;

        util::Amount discountAmount = event.getDiscountAmount();
        if (util::Amount(0) < discountAmount)
            std::cout
                << "Discount: " << discountAmount << std::endl;

        std::cout
            << "Gross price:  " << event.getGrossPrice() << std::endl
            << "Sales tax:    " << event.getTotalTax() << std::endl
            << "---" << std::endl
            << "Net price:    " << event.getNetPrice() << std::endl
            << "Cash payment: " << event.getpaidAmount() << std::endl
            << "Change:       " << event.getChangeAmount() << std::endl
            << std::endl;
    }
}
