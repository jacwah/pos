#include "integration/receipt_printer.h"
#include <iomanip>

namespace integration {

void ReceiptPrinter::handleSaleEvent(const SaleEvent& event)
{
        stream
            << std::endl
            << "=== Receipt ===" << std::endl
            << "Time: " << event.getTimestamp() << std::endl
            << std::endl
            << "Id Item                Price" << std::endl
            << "----------------------------" << std::endl;

        for (auto& record : event.getItems()) {
            stream
                << std::setw(2) << std::setfill('0') << std::right << record.getItemId() << " ";
            stream
                << std::setw(20) << std::setfill(' ') << std::left << record.getItem().getDescription();
            stream
                << record.getTotalPrice() << std::endl;

            int quantity = record.getQuantity();
            if (quantity > 1)
                stream
                    << "    " << quantity << " x " << record.getItem().getPrice() << std::endl;
        }

        stream << std::endl;

        util::Amount discountAmount = event.getDiscountAmount();
        if (util::Amount(0) < discountAmount)
            stream
                << "Discount: " << discountAmount << std::endl;

        stream
            << "Gross price:  " << event.getGrossPrice() << std::endl
            << "Sales tax:    " << event.getTotalTax() << std::endl
            << "---" << std::endl
            << "Net price:    " << event.getNetPrice() << std::endl
            << "Cash payment: " << event.getpaidAmount() << std::endl
            << "Change:       " << event.getChangeAmount() << std::endl
            << std::endl;
    }
}
