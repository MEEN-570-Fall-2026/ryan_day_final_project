#ifndef VIEWERAPI
#define VIEWERAPI

#include <vector>
#include "RuntimeValue.hpp"

class ViewerAPI {
    public:
        ViewerAPI() = default;
        virtual RuntimeValue invoke(const std::string& method, const std::vector<RuntimeValue>& args);

    protected:
        virtual void add_objects(const std::vector<RuntimeValue>& args) = 0;
};

#endif