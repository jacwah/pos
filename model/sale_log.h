#pragma once

#include <vector>

#include "integration/dto.h"
#include "integration/sale_log_observer.h"

namespace model {

class SaleLog {
    std::vector<std::unique_ptr<integration::SaleLogObserver>> observers;

public:
    SaleLog() : observers() {}
    SaleLog(SaleLog&& other)
    {
        std::swap(observers, other.observers);
    }

    // This is a non-copy type because of std::unique_ptr!
    SaleLog(const SaleLog&) = delete;
    SaleLog& operator=(const SaleLog&) = delete;

    void observe(std::unique_ptr<integration::SaleLogObserver> observer)
    {
        observers.push_back(std::move(observer));
    }

    void append(const integration::SaleEvent& event)
    {
        for (auto& observer : observers)
            observer->handleSaleEvent(event);
    }
};

}
