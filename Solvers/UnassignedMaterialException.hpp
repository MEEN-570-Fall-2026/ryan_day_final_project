#include <stdexcept>
#include <string>

class UnassignedMaterialException : public std::runtime_error {
    public:
        explicit UnassignedMaterialException(const std::string& message): std::runtime_error(message) {}
};