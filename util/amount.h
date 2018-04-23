#pragma once

namespace util {

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

}

std::ostream& operator<<(std::ostream& os, const util::Amount& amount)
{
    os << "$" << static_cast<double>(amount);
    return os;
}
