#include "catch.hpp"
#include "integration/receipt_printer.h"
#include <sstream>

TEST_CASE("Receipt printer gives correct output")
{
    std::stringstream stream;
    integration::ReceiptPrinter receiptPrinter(stream);

    SECTION("Nothing sold")
    {
        integration::SaleEvent event(
            {},
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0)
        );
        receiptPrinter.handleSaleEvent(event);

        REQUIRE_THAT(stream.str(), Catch::Contains("Time: "));
        REQUIRE_THAT(stream.str(), Catch::Contains("Gross price:  $0"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Sales tax:    $0"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Net price:    $0"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Cash payment: $0"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Change:       $0"));
    }

    SECTION("No discount")
    {
        integration::SaleEvent event(
            {},
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0)
        );
        receiptPrinter.handleSaleEvent(event);

        REQUIRE_THAT(stream.str(), !Catch::Contains("Discount: "));
    }

    SECTION("Discount")
    {
        integration::SaleEvent event(
            {},
            util::Amount(5),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0),
            util::Amount(0)
        );
        receiptPrinter.handleSaleEvent(event);

        REQUIRE_THAT(stream.str(), Catch::Contains("Discount: $5"));
    }

    SECTION("One item sold")
    {
        util::Amount netPrice(7);
        util::Amount grossPrice(5);
        util::Amount taxAmount(2);
        util::Amount paid(10);
        util::Amount change(3);
        integration::ItemId itemId(1);
        integration::Item item("Test item", grossPrice);
        integration::SoldItemRecord soldItem(itemId, item, 1, grossPrice);
        integration::SaleEvent event(
            {soldItem},
            util::Amount(0),
            grossPrice,
            taxAmount,
            netPrice,
            paid,
            change
        );
        receiptPrinter.handleSaleEvent(event);

        REQUIRE_THAT(stream.str(), Catch::Matches("(?:.|\n)*\n01 Test item\\s*\\$5\n(?:.|\n)*"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Time: "));
        REQUIRE_THAT(stream.str(), Catch::Contains("$5"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Gross price:  $5"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Sales tax:    $2"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Net price:    $7"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Cash payment: $10"));
        REQUIRE_THAT(stream.str(), Catch::Contains("Change:       $3"));
    }
}
