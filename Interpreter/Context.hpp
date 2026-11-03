#ifndef CONTEXT
#define CONTEXT

#include <unordered_map>
#include "RuntimeValue.hpp"

class Context {
    public:
        Context() = default;
        void add(std::string variableName, RuntimeValue value);
        RuntimeValue get(std::string variableName);

    private:
        std::unordered_map<std::string, RuntimeValue> variableMap; 

};

#endif