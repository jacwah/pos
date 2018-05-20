#include <iostream>
#include "view/terminal_view.h"
#include "view/total_revenue_view.h"
#include "controller/sale_controller_builder.h"
#include "model/discount_rules.h"
#include "model/shopping_cart_factory.h"
#include "model/sale_log.h"
#include "integration/catalog_creator.h"
#include "integration/sale_observer_creator.h"

namespace startup {

static std::shared_ptr<model::SaleLog> setupSaleLogging()
{
    auto observers = integration::createSaleObservers();
    observers.emplace_back(std::make_unique<view::TotalRevenueView>());
    auto log = std::make_shared<model::SaleLog>();

    for (auto& observer : observers)
        log->observe(std::move(observer));

    return log;
}

static void main()
{
    integration::CatalogCreator catalogCreator;
    integration::ItemCatalog itemCatalog = catalogCreator.getItemCatalog();
    auto discountRules = std::make_shared<model::DiscountRules>(catalogCreator);
    model::ShoppingCartFactory cartFactory(catalogCreator);
    auto saleLog = setupSaleLogging();
    controller::SaleControllerBuilder saleControllerBuilder(discountRules);
    saleControllerBuilder.setSaleLog(saleLog);
    view::TerminalView view(saleControllerBuilder, cartFactory);

    view.runLoop();
}

}

int main(int argc, char *argv[])
{
    startup::main();
    return 0;
}
