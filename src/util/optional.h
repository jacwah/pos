#pragma once

/* Apple has not yet moved optional from std::experimental. Wrap it in a type
 * here to work around the issue.
 */

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
