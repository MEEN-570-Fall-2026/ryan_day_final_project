#ifndef OBJECTFACTORY
#define OBJECTFACTORY

#include <vector>
#include <functional>
#include <map>
#include <string>
#include "RuntimeValue.hpp"

class ObjectFactory {
    public:
        using Arguments = std::vector<RuntimeValue>;
        using CADObjectPointer = RuntimeValue::CADObjectPointer;
        using Creator = std::function<CADObjectPointer(const Arguments&)>;

        ObjectFactory();

        void register_type(std::string name, Creator creator) {
            auto [it, inserted] = creators.emplace(std::move(name), std::move(creator));
            if (!inserted) {
                throw std::runtime_error("Object type already registered");
            }
        }

        CADObjectPointer create(const std::string& name, const Arguments& args) const
        {
            auto it = creators.find(name);
            if (it == creators.end()) {
                throw std::runtime_error("Unknown object type: " + name);
            }
            return it->second(args);
        }

    private:
        std::unordered_map<std::string, Creator> creators;
};

#endif