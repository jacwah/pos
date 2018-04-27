#pragma once

#include "integration/sale_log_observer.h"

namespace integration {

class RecieptPrinter : public SaleLogObserver {
    virtual void handleSaleEvent(const SaleEvent& event);
};

}
