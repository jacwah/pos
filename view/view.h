#pragma once

#include "controller/sale_controller.h"
#include "controller/sale_controller_factory.h"
#include "controller/entering_controller.h"
#include "model/shopping_cart_factory.h"
#include "model/shopping_cart_summary.h"
#include "integration/dto.h"

namespace view {

class View {
    controller::SaleControllerFactory saleControllerFactory;
    model::ShoppingCartFactory shoppingCartFactory;

public:
    View(
            controller::SaleControllerFactory saleControllerFactory,
            model::ShoppingCartFactory shoppingCartFactory)
        : saleControllerFactory(saleControllerFactory)
        , shoppingCartFactory(shoppingCartFactory)
    {}

    void simulateUser()
    {
        integration::ItemId itemsToBeEntered[] =    { 0, 1, 2, 3, 1 };
        int quantitiesToBeEntered[] =               { 1, 4, 2, 1, 2 };

        controller::EnteringController enteringController(shoppingCartFactory);

        for (int i = 0; i < sizeof(itemsToBeEntered) / sizeof(itemsToBeEntered[0]); ++i) {
            model::ShoppingCartSummary summary = enteringController.enterItem(
                    itemsToBeEntered[i],
                    quantitiesToBeEntered[i]);

            util::optional<integration::Item> item = summary.getLastAddedItem();
            if (item) {
                std::cout << "Added: " << *item << std::endl;
                std::cout << "Gross price: " << summary.getGrossPrice() << std::endl;
            } else {
                std::cout << "Item identifier not found!" << std::endl;
            }
        }

        controller::SaleController saleController = enteringController.finish(saleControllerFactory);

        std::cout << "Net price: " << saleController.getNetPrice() << std::endl;

        saleController.requestDiscount(integration::CustomerId(1));
        std::cout << "Net price after discount: " << saleController.getNetPrice() << std::endl;

        util::optional<util::Amount> change = saleController.payAndGetChange(20);
        if (change)
            std::cout << "Change: " << *change << std::endl;
        else
            std::cout << "Payed amount insufficient!" << std::endl;
    }
};

}
