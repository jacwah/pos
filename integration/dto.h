#pragma once

#include <cassert>

namespace integration {

class Amount {
    double value;

    public:
    Amount(double value) : value(value) {}

    bool operator<=(Amount other) const
    {
        return value <= other.value;
    }

    Amount operator*(double other) const
    {
        return value * other;
    }

    explicit operator double() const
    {
        return value;
    }
};

// TODO: Not really a DTO?
class Percentage {
    double value;

    public:
    Percentage(double value) : value(value)
    {
        assert(0.0 <= value);
        assert(value <= 1.0);
    }

    Amount deductFrom(Amount amount) const
    {
        return amount * (1 - value);
    }

    explicit operator double() const
    {
        return value;
    }
};

typedef int CustomerId;

class Customer {
    std::string name;
    Percentage discount;

    public:
    Customer(std::string name, Percentage discount) : name(name), discount(discount) {}

    const Percentage getDiscountPercentage() const
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
    Amount price;

    public:
    Item(std::string description, Amount price) : description(description), price(price) {}

    const std::string& getDescription() const
    {
        return description;
    }

    const Amount& getPrice() const
    {
        return price;
    }
};

class SaleEvent {
    int time;

    public:
    SaleEvent(int time) : time(time) {}

    int getTime() const
    {
        return time;
    }
};

}

std::ostream& operator<<(std::ostream& os, const integration::Amount& amount)
{
    os << "$" << static_cast<double>(amount);
    return os;
}

std::ostream& operator<<(std::ostream& os, const integration::Percentage& percentage)
{
    os << static_cast<double>(percentage) << "%";
    return os;
}

std::ostream& operator<<(std::ostream& os, const integration::Item& item)
{
    os << item.getDescription() << " (" << item.getPrice() << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const integration::Customer& customer)
{
    os << customer.getName() << " (" << customer.getDiscountPercentage() << " off)";
    return os;
}
