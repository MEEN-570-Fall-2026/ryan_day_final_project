#ifndef CADOBJECT
#define CADOBJECT

#include <string>
#include <vector>
#include "RuntimeValue.hpp"

class CADObject {
    public:
        virtual ~CADObject() = default;
        virtual RuntimeValue invoke(const std::string& method, const std::vector<RuntimeValue>& args) = 0;
};

#endif