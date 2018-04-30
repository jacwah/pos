#pragma once

#include <vector>

#include "integration/dto.h"
#include "integration/sale_log_observer.h"

namespace model {

/**
 * Represents an abstract log of completed sales. Is used to dispatch sale
 * events to {@link integration::SaleLogObserver}s.
 */
class SaleLog {
    std::vector<std::unique_ptr<integration::SaleLogObserver>> observers;

public:
    /**
     * Create a new instance with no observers.
     */
    SaleLog()
        : observers()
    {}

    /**
     * Create a new instance with observers by moving from <code>other</code>
     * instance.
     *
     * @param other The instance to move from.
     */
    SaleLog(SaleLog&& other)
    {
        std::swap(observers, other.observers);
    }

    /**
     * Add an observer to be notified of new sales.
     *
     * @param observer The object to be notified.
     */
    void observe(std::unique_ptr<integration::SaleLogObserver> observer)
    {
        observers.push_back(std::move(observer));
    }

    /**
     * Append a sale event to the log by notifying observers.
     *
     * @param event The event to dispatch.
     */
    void append(const integration::SaleEvent& event)
    {
        for (auto& observer : observers)
            observer->handleSaleEvent(event);
    }
};

}
