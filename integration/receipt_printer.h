#pragma once

#include <iostream>
#include "integration/sale_log_observer.h"

namespace integration {

class RecieptPrinter : public SaleLogObserver {
    public:
    virtual void handleSaleEvent(const SaleEvent& event) {
        std::cout << "Receipt: time=" << event.getTimestamp() << std::endl;
    }
};

}
