#include "integration/sale_log_observer.h"
#include "util/optional.h"
#include <sstream>

struct MockObserver : public integration::SaleLogObserver {
    int& numEvents;
    util::optional<integration::SaleEvent>& lastEvent;

    MockObserver(int& numEvents, util::optional<integration::SaleEvent>& lastEvent)
        : numEvents(numEvents)
        , lastEvent(lastEvent)
    {}

    virtual void handleSaleEvent(const integration::SaleEvent& event)
    {
        lastEvent = event;
        ++numEvents;
    }
};
