#include "catch.hpp"
#include "model/sale.h"
#include "helper/mock_observer.h"

TEST_CASE("Sale")
{
    integration::ItemCatalog itemCatalog;
    model::Discount discount(util::Percentage(0.25));
    double taxFactor = 1.25;

    SECTION("No items")
    {
        model::ShoppingCart shoppingCart(itemCatalog);
        model::Sale sale(shoppingCart);

        SECTION("Net price")
        {
            REQUIRE(sale.calculateNetPrice() == 0.0);
        }

        SECTION("Net price with discount")
        {
            sale.setDiscount(discount);
            REQUIRE(sale.calculateNetPrice() == 0.0);
        }
    }

    SECTION("Some items")
    {
        int numEvents = 0;
        util::optional<integration::SaleEvent> lastEvent;
        model::SaleLog saleLog;
        saleLog.observe(std::make_unique<MockObserver>(numEvents, lastEvent));

        model::ShoppingCart shoppingCart(itemCatalog);
        integration::ItemId itemId(1);
        integration::Item item = itemCatalog.find(itemId);
        shoppingCart.addItem(integration::ItemId(1), 2);
        model::Sale sale(shoppingCart);

        SECTION("Net price")
        {
            REQUIRE(sale.calculateNetPrice()
                    == Approx(item.getPrice() * 2 * taxFactor));
        }

        SECTION("Net price with discount")
        {
            sale.setDiscount(discount);
            REQUIRE(sale.calculateNetPrice()
                    == Approx(item.getPrice() * 2 * taxFactor * 0.75));
        }

        SECTION("Complete")
        {
            SECTION("fails on insufficient paid amount")
            {
                REQUIRE_FALSE(sale.complete(item.getPrice(), saleLog));
                REQUIRE(numEvents == 0);
            }

            SECTION("succeeds if amount is equal to net price and generates correct event")
            {
                util::Amount paid = sale.calculateNetPrice();
                auto change = sale.complete(paid, saleLog);
                REQUIRE(change);
                REQUIRE(*change == Approx(0));

                REQUIRE(numEvents == 1);
                CHECK(lastEvent->getChangeAmount() == *change);
                CHECK(lastEvent->getDiscountAmount() == 0.0);
                CHECK(lastEvent->getGrossPrice() == shoppingCart.calculateGrossPrice());
                CHECK(lastEvent->getTotalTax()
                        == Approx(shoppingCart.calculateGrossPrice() * (taxFactor - 1)));
                CHECK(lastEvent->getNetPrice() == sale.calculateNetPrice());
                CHECK(lastEvent->getPaidAmount() == paid);
            }

            SECTION("succeeds if amount is greater than net price and generates correct event")
            {
                util::Amount paid = sale.calculateNetPrice() + 10;
                auto change = sale.complete(paid, saleLog);
                REQUIRE(change);
                REQUIRE(*change == Approx(paid - sale.calculateNetPrice()));

                REQUIRE(numEvents == 1);
                CHECK(lastEvent->getChangeAmount() == *change);
                CHECK(lastEvent->getDiscountAmount() == 0.0);
                CHECK(lastEvent->getGrossPrice() == shoppingCart.calculateGrossPrice());
                CHECK(lastEvent->getTotalTax()
                        == Approx(shoppingCart.calculateGrossPrice() * (taxFactor - 1)));
                CHECK(lastEvent->getNetPrice() == sale.calculateNetPrice());
                CHECK(lastEvent->getPaidAmount() == paid);
            }

            SECTION("succeeds if amount is greater than net price and generates correct event"
                    " with discount")
            {
                sale.setDiscount(discount);
                util::Amount paid = sale.calculateNetPrice() + 10;
                auto change = sale.complete(paid, saleLog);
                REQUIRE(change);
                REQUIRE(*change == Approx(paid - sale.calculateNetPrice()));

                REQUIRE(numEvents == 1);
                CHECK(lastEvent->getChangeAmount() == *change);
                CHECK(lastEvent->getDiscountAmount() == Approx(shoppingCart.calculateGrossPrice() * 0.25));
                CHECK(lastEvent->getGrossPrice() == shoppingCart.calculateGrossPrice());
                CHECK(lastEvent->getTotalTax()
                        == Approx(discount.applyTo(shoppingCart.calculateGrossPrice()) * (taxFactor - 1)));
                CHECK(lastEvent->getNetPrice() == sale.calculateNetPrice());
                CHECK(lastEvent->getPaidAmount() == paid);
            }
        }
    }
}
