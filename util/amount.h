#pragma once

namespace util {

class Amount {
    double value;

public:
    Amount() : value(0) {}
    Amount(double value) : value(value) {}

    bool operator<(Amount other) const
    {
        return value < other.value;
    }

    Amount operator*(double other) const
    {
        return value * other;
    }

    Amount operator+(Amount other) const
    {
        return value + other.value;
    }

    Amount operator-(Amount other) const
    {
        return value - other.value;
    }

    Amount& operator+=(Amount other)
    {
        value += other.value;
        return *this;
    }

    explicit operator double() const
    {
        return value;
    }
};

}

std::ostream& operator<<(std::ostream& os, const util::Amount& amount)
{
    os << "$" << static_cast<double>(amount);
    return os;
}
