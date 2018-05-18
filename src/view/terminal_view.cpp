#include "view/terminal_view.h"
#include "controller/entering_controller.h"
#include "controller/sale_controller.h"
#include "integration/dto.h"
#include "util/optional.h"
#include "util/logger.h"
#include <iostream>

namespace view {

class ItemIdRecord {
    integration::ItemId itemId;
    int quantity;

    ItemIdRecord(integration::ItemId itemId, int quantity)
        : itemId(itemId)
        , quantity(quantity)
    {}

public:
    static util::optional<ItemIdRecord> parse(const std::string& string)
    {
        try {
            size_t len = 0;
            integration::ItemId itemId = std::stoi(string, &len);
            int quantity = 1;

            if (len < string.size()) {
                std::string rest = string.substr(len + 1);
                quantity = std::stoi(rest);
            }

            return ItemIdRecord(itemId, quantity);
        } catch (const std::logic_error& error) {
            std::cout << "Syntax error! (" << error.what() << ")" << std::endl;
            return {};
        }
    }

    integration::ItemId getItemId() const
    {
        return itemId;
    }

    int getQuatity() const
    {
        return quantity;
    }
};

static util::optional<int> parseInt(const std::string& string)
{
    try {
        return std::stoi(string);
    } catch (const std::logic_error& error) {
        std::cout << "Syntax error! (" << error.what() << ")" << std::endl;
        return {};
    }
}

static util::optional<int> getAndParseInt()
{
    std::string input;
    std::getline(std::cin, input);
    return parseInt(input);
}

void TerminalView::runLoop()
{
    while (!std::cin.eof()) {
        runSingle();
        std::cout << "==========" << std::endl;
    }

    std::cout << std::endl;
}

void TerminalView::handleException(const char *userMessage, const std::exception& exception)
{
    util::Logger::getInstance().logException(exception);
    errorMessageHandler.displayError(userMessage);
}

void TerminalView::runSingle()
{
    std::cout
        << "Enter item id, optionally followed by a separator and then quantity." << std::endl
        << "Enter blank line to finalize sale." << std::endl;

    controller::EnteringController enteringController(shoppingCartFactory);

    for (std::string line; std::cout << "Enter item [quantity]> ", std::getline(std::cin, line); ) {
        if (line.empty())
            break;

        util::optional<ItemIdRecord> record = ItemIdRecord::parse(line);

        if (record) {
            int quantity = record->getQuatity();
            integration::ItemId itemId = record->getItemId();

            if (quantity < 1) {
                errorMessageHandler.displayError("Quantity must be positive.");
            } else {
                try {
                    model::ShoppingCartSummary summary = enteringController.enterItem(itemId, quantity);
                    auto item = summary.getLastAddedItem();
                    std::cout << "Added " << quantity << " " << item.getDescription() << std::endl;
                }
                catch (const integration::InvalidItemIdException& exception) {
                    handleException("Item not found.", exception);
                }
                catch (const controller::OperationFailedException& exception) {
                    handleException(
                            "Operation failed. Please try again later.",
                            exception);
                }
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
            handleException("Syntax error.", error);
        }
    }

    bool finished = false;
    while (!finished) {
        util::optional<int> paidAmount;
        while (!paidAmount) {
            std::cout << "Enter paid amount> ";
            paidAmount = getAndParseInt();
        }

        util::optional<util::Amount> change = saleController.payAndGetChange(*paidAmount);
        if (change) {
            std::cout << "Change: " << *change << std::endl;
            finished = true;
        } else {
            errorMessageHandler.displayError("Insufficient amount.");
        }
    }
}

}
