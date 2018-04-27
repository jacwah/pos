#include <iostream>
#include "view/terminal_view.h"
#include "controller/sale_controller_factory.h"
#include "model/discount_rules.h"
#include "model/shopping_cart_factory.h"
#include "model/sale_log.h"
#include "integration/catalog_creator.h"
#include "integration/sale_observer_creator.h"

namespace startup {

static model::SaleLog setupSaleLogging()
{
    auto observers = integration::createSaleObservers();
    model::SaleLog log;

    for (auto& observer : observers)
        log.observe(std::move(observer));

    return log;
}

static void main()
{
    integration::CatalogCreator catalogCreator;
    integration::ItemCatalog itemCatalog = catalogCreator.getItemCatalog();
    model::DiscountRules discountRules(catalogCreator);
    model::ShoppingCartFactory cartFactory(catalogCreator);
    model::SaleLog saleLog = setupSaleLogging();
    controller::SaleControllerFactory saleControllerFactory(discountRules, saleLog);
    view::TerminalView view(saleControllerFactory, cartFactory);

    view.runLoop();
}

}

int main(int argc, char *argv[])
{
    startup::main();
    return 0;
}
