#include <stdexcept>
#include <string>

class UnassignedConstraintException : public std::runtime_error {
    public:
        explicit UnassignedConstraintException(const std::string& message): std::runtime_error(message) {}
};