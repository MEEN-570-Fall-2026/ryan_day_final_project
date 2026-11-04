#ifndef VIEWERAPI
#define VIEWERAPI

#include <vector>
#include "RuntimeValue.hpp"
#include <string>

class ViewerAPI {
    public:
        ViewerAPI() = default;
        RuntimeValue invoke(const std::string& method, const std::vector<RuntimeValue>& args);

    protected:
        virtual void add_objects(const std::vector<RuntimeValue>& args) = 0;
};

#endif