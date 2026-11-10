#include "Context.hpp"
#include "ViewerAPI.hpp"
#include <iostream>
#include "ContextException.hpp"

Context::Context(std::shared_ptr<ViewerAPI> viewerSharedPointer)
{
    variableMap["Viewer"] = RuntimeValue(viewerSharedPointer);
}

Context::Context(std::shared_ptr<ViewerAPI> viewerSharedPointer, std::shared_ptr<Mesher> mesherSharedPointer)
{
    variableMap["Viewer"] = RuntimeValue(viewerSharedPointer);
    variableMap["Mesher"] = RuntimeValue(mesherSharedPointer);
}

void Context::add(std::string variableName, RuntimeValue value)
{
    variableMap[variableName] = value;
}

RuntimeValue Context::get(std::string variableName)
{
    try {
        std::cout << "Getting: " << variableName << std::endl;
        return variableMap.at(variableName);
    }
    catch (std::out_of_range) {
        throw ContextException(variableName);
    }
}
