#pragma once

#include "util/percentage.h"
#include "util/amount.h"

namespace integration {

typedef int CustomerId;

class Customer {
    std::string name;
    util::Percentage discount;

    public:
    Customer(std::string name, util::Percentage discount) : name(name), discount(discount) {}

    const util::Percentage getDiscountPercentage() const
    {
        return {discount};
    }

    const std::string getName() const
    {
        return name;
    }
};

typedef int ItemId;

class Item {
    std::string description;
    util::Amount price;

public:
    Item(std::string description, util::Amount price) : description(description), price(price) {}

    Item(const Item& other)
        : description(other.description)
        , price(other.price)
    {}

    const std::string& getDescription() const
    {
        return description;
    }

    const util::Amount& getPrice() const
    {
        return price;
    }
};


class SoldItemRecord {
    ItemId itemId;
    Item item;
    int quantity;
    util::Amount totalPrice;

public:
    SoldItemRecord(ItemId itemId, Item item, int quantity, util::Amount totalPrice)
        : itemId(itemId)
        , item(item)
        , quantity(quantity)
        , totalPrice(totalPrice)
    {}

    ItemId getItemId() const
    {
        return itemId;
    }

    const Item& getItem() const
    {
        return item;
    }

    int getQuantity() const
    {
        return quantity;
    }

    util::Amount getTotalPrice() const
    {
        return totalPrice;
    }

    bool operator<(const SoldItemRecord& other) const
    {
        return itemId < other.itemId;
    }
};

}

inline std::ostream& operator<<(std::ostream& os, const integration::Item& item)
{
    os << item.getDescription();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const integration::Customer& customer)
{
    os << customer.getName() << " (" << customer.getDiscountPercentage() << " off)";
    return os;
}
