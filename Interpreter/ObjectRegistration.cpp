#include "ObjectRegistration.hpp"
#include "ObjectFactory.hpp"
#include "Point.hpp"
#include "primitives3d/Cube.hpp"

void register_objects(ObjectFactory & factory)
{
    factory.register_type("Point", create_point);
    factory.register_type("Cube", create_cube);
}


RuntimeValue::CADObjectPointer create_point(const std::vector<RuntimeValue>& args)
{
    if (args.size() == 3) {
        return std::make_shared<Point>(
            args[0].as_number(),
            args[1].as_number(),
            args[2].as_number()
        );
    }
}

RuntimeValue::CADObjectPointer create_cube(const std::vector<RuntimeValue>& args)
{
    if (args.size() == 3) {
        return std::make_shared<Cube>(
            args[0].as_number(),
            args[1].as_number(),
            args[2].as_number()
        );
    }
    else if (args.size() == 4) {
        auto retrievedObject = args[0].as<RuntimeValue::CADObjectPointer>();
        auto pointArgument = std::dynamic_pointer_cast<Point>(retrievedObject);
        return std::make_shared<Cube>(
            *pointArgument,
            args[1].as_number(),
            args[2].as_number(),
            args[3].as_number()
        );
    }
}



