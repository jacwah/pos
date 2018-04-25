#pragma once

#ifdef __APPLE__
#include <experimental/optional>
#else
#include <optional>
#endif

namespace util {

#ifdef __APPLE__
using std::experimental::optional;
#else
using std::optional;
#endif

}
