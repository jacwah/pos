#include "view/terminal_view.h"
#include "controller/entering_controller.h"
#include "controller/sale_controller.h"
#include "integration/dto.h"
#include <iostream>

namespace view {

void TerminalView::runLoop()
{
    while (!std::cin.eof()) {
        runSingle();
        std::cout << "==========" << std::endl;
    }

    std::cout << std::endl;
}

void TerminalView::runSingle()
{
    std::cout << "Enter item id, optionally followed by a separator and then quantity." << std::endl
        << "Enter empty line to finialize sale." << std::endl;

    controller::EnteringController enteringController(shoppingCartFactory);

    for (std::string line; std::cout << "Enter item [quantity]> ", std::getline(std::cin, line); ) {
        if (line.empty())
            break;

        util::optional<ItemIdRecord> record = parseItemEnter(line);

        if (record) {
            if (record->quantity < 1) {
                std::cout << "Error: quantity must be positive" << std::endl;
            } else {
                model::ShoppingCartSummary summary = enteringController.enterItem(record->itemId, record->quantity);
                util::optional<integration::Item> item = summary.getLastAddedItem();

                if (item)
                    std::cout << "Added " << record->quantity << " " << *item << std::endl;
                else
                    std::cout << "Error: item not found" << std::endl;
            }

        }
    }

    controller::SaleController saleController = enteringController.finish(saleControllerFactory);
    std::cout << "Net price: " << saleController.getNetPrice() << std::endl;

    std::cout << "Enter customer id or empty> ";
    std::string idString;
    std::getline(std::cin, idString);
    if (!idString.empty()) {
        try {
            integration::CustomerId customerId = std::stoi(idString);
            saleController.requestDiscount(customerId);
            std::cout << "Net price: " << saleController.getNetPrice() << std::endl;
        } catch (const std::logic_error& error) {
            std::cout << "Syntax error! (" << error.what() << ")" << std::endl;
        }
    }

    bool finished = false;
    while (!finished) {
        util::optional<int> payedAmount;
        while (!payedAmount) {
            std::cout << "Enter payed amount> ";
            payedAmount = getAndParseInt();
        }

        util::optional<util::Amount> change = saleController.payAndGetChange(*payedAmount);
        if (change) {
            // printed on reciept already
            //std::cout << "Change: " << *change << std::endl;
            finished = true;
        } else {
            std::cout << "Error: insufficient amount!" << std::endl;
        }
    }
}

util::optional<int> TerminalView::getAndParseInt() const
{
    std::string input;
    std::getline(std::cin, input);
    return parseInt(input);
}

util::optional<int> TerminalView::parseInt(const std::string& string) const
{
    try {
        return std::stoi(string);
    } catch (const std::logic_error& error) {
        std::cout << "Syntax error! (" << error.what() << ")" << std::endl;
        return {};
    }
}

util::optional<ItemIdRecord> TerminalView::parseItemEnter(const std::string& line) const
{
    try {
        size_t len = 0;
        integration::ItemId itemId = std::stoi(line, &len);
        int quantity = 1;

        if (len < line.size()) {
            std::string rest = line.substr(len + 1);
            quantity = std::stoi(rest);
        }

        return ItemIdRecord(itemId, quantity);
    } catch (const std::logic_error& error) {
        std::cout << "Syntax error! (" << error.what() << ")" << std::endl;
        return {};
    }
}

}
