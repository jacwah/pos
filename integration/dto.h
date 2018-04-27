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

}

inline std::ostream& operator<<(std::ostream& os, const integration::Item& item)
{
    os << item.getDescription() << " (" << item.getPrice() << ")";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const integration::Customer& customer)
{
    os << customer.getName() << " (" << customer.getDiscountPercentage() << " off)";
    return os;
}
