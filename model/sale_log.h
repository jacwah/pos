#pragma once

#include "integration/dto.h"
#include "integration/sale_log_observer.h"

namespace model {

class SaleLog {
    std::vector<std::shared_ptr<integration::SaleLogObserver>> observers;

    public:
    void observe(std::shared_ptr<integration::SaleLogObserver> observer)
    {
        observers.push_back(observer);
    }

    void append(const integration::SaleEvent& event) const
    {
        for (auto observer : observers)
            observer->handleSaleEvent(event);
    }
};

}
