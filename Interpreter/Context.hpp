#ifndef CONTEXT
#define CONTEXT

#include <unordered_map>
#include "RuntimeValue.hpp"
#include "Mesher.hpp"

class Context {
    public:
        Context() = default;
        Context(std::shared_ptr<ViewerAPI> viewerSharedPointer);
        Context(std::shared_ptr<ViewerAPI> viewerSharedPointer, std::shared_ptr<Mesher> mesherSharedPointer);
        void add(std::string variableName, RuntimeValue value);
        RuntimeValue get(std::string variableName);

    private:
        std::unordered_map<std::string, RuntimeValue> variableMap; 

};

#endif