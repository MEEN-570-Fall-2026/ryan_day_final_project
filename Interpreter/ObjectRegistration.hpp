#ifndef OBJECTREGISTRATION
#define OBJECTREGISTRATION

#include "RuntimeValue.hpp"
#include <vector>

class ObjectFactory;

void register_objects(ObjectFactory& factory);
RuntimeValue::CADObjectPointer create_point(const std::vector<RuntimeValue>& args);
RuntimeValue::CADObjectPointer create_cube(const std::vector<RuntimeValue>& args);


#endif