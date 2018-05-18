#pragma once

namespace controller {

/**
 * Indicates that a system operation failed.
 */
class OperationFailedException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

}
