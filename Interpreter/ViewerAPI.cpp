#include "viewerAPI.hpp"

RuntimeValue ViewerAPI::invoke(const std::string &method, const std::vector<RuntimeValue>& args)
{
    if (method == "add_objects" && args.size() != 0)
    {
        render(args);
        return RuntimeValue{};
    }
    throw std::runtime_error("Unknown method " + method + " with supplied arguments!");
}