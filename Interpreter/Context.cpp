#include "Context.hpp"
#include "ViewerAPI.hpp"
#include <iostream>
#include "ContextException.hpp"

Context::Context(std::shared_ptr<ViewerAPI> viewerSharedPointer)
{
    variableMap["Viewer"] = RuntimeValue(viewerSharedPointer);
}

void Context::add(std::string variableName, RuntimeValue value)
{
    variableMap[variableName] = value;
}

RuntimeValue Context::get(std::string variableName)
{
    try {
        std::cout << "Getting: " << variableName << std::endl;
        return variableMap[variableName];
    }
    catch (std::out_of_range) {
        throw ContextException(variableName);
    }
}
