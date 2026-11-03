#include "Context.hpp"

void Context::add(std::string variableName, RuntimeValue value)
{
    variableMap[variableName] = value;
}

RuntimeValue Context::get(std::string variableName)
{
    return variableMap[variableName];
}
