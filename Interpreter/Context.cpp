#include "Context.hpp"
#include "ViewerAPI.hpp"
#include <iostream>

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
    std::cout << "Getting: " << variableName << std::endl;
    return variableMap[variableName];
}
