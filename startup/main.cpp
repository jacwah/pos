#include <iostream>
#include "controller/controller.h"
#include "model/discount_rules.h"
#include "model/shopping_cart_factory.h"
#include "model/sale_log.h"
#include "integration/catalog_creator.h"
#include "integration/dto.h"
#include "integration/sale_observer_creator.h"
#include "util/amount.h"
#include "util/percentage.h"

namespace startup {

model::SaleLog setupSaleLogging()
{
    auto observers = integration::createSaleObservers();
    model::SaleLog log;

    for (auto observer : observers)
        log.observe(observer);

    return log;
}

void main()
{
    integration::CatalogCreator catalogCreator;
    integration::ItemCatalog itemCatalog = catalogCreator.getItemCatalog();
    model::DiscountRules discountRules(catalogCreator);
    model::ShoppingCartFactory cartFactory(catalogCreator);
    model::SaleLog saleLog = setupSaleLogging();
    controller::Controller controller(cartFactory, discountRules, saleLog);

    if (auto item = itemCatalog.find(0))
        std::cout << *item << std::endl;
    else
        std::cout << "Invalid item id" << std::endl;

    if (auto item = itemCatalog.find(1))
        std::cout << *item << std::endl;
    else
        std::cout << "Invalid item id" << std::endl;

    model::Discount d0 = discountRules.getDiscountFor(0);
    model::Discount d1 = discountRules.getDiscountFor(1);

    std::cout << d0.applyTo(util::Amount(1.0)) << std::endl;
    std::cout << d1.applyTo(util::Amount(1.0)) << std::endl;

    saleLog.append(integration::SaleEvent(0));
    saleLog.append(integration::SaleEvent(1));
}

}

int main(int argc, char *argv[])
{
    startup::main();
    return 0;
}
