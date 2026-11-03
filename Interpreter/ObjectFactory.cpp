#include "ObjectFactory.hpp"
#include "ObjectRegistration.hpp"

ObjectFactory::ObjectFactory()
{
    register_objects(*this);
}