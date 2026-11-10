#include "RuntimeValue.hpp"

RuntimeValue::RuntimeValue(int value) : value{value}
{
}

RuntimeValue::RuntimeValue(double value) : value{value}
{
}

RuntimeValue::RuntimeValue(bool value) : value{value}
{
}

RuntimeValue::RuntimeValue(CADObjectPointer value) : value{value}
{
}

RuntimeValue::RuntimeValue(ViewerAPIPointer value) : value{value}
{
}

RuntimeValue::RuntimeValue(MesherPointer value) : value{value}
{
}

RuntimeValue::RuntimeValue(MeshPointer value) : value{value}
{
}

double RuntimeValue::as_number() const
{
    if (const auto* stored = std::get_if<int>(&value)) {
        return static_cast<double>(*stored);
    }
    if (const auto* stored = std::get_if<double>(&value)) {
        return* stored;
    }
    throw std::runtime_error("Expected a number");
}
