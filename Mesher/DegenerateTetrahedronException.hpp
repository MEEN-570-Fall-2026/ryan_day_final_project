#include <stdexcept>
#include <string>

class DegenerateTetrahedronException : public std::runtime_error {
    public:
        explicit DegenerateTetrahedronException(const std::string& message): std::runtime_error(message) {}
};