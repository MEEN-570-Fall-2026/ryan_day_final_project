#include "Mesher.hpp"
#include "Mesh.hpp"
#include "Point.hpp"
#include <memory>
#include <iostream>

Mesh& Mesher::create_mesh(Object3d& geometry, double elementSizeX, double elementSizeY, double elementSizeZ)
{
    std::vector<Point> geometry_vertices = geometry.get_vertices();
    std::vector<std::shared_ptr<Point>> vertexPointers;
    for (Point& vertex : geometry_vertices)
    {
        vertexPointers.push_back(std::make_shared<Point>(vertex));
    }
    MeshPointer meshPtr = std::make_shared<Mesh>(std::move(vertexPointers), elementSizeX, elementSizeY, elementSizeZ);
    meshes.push_back(std::move(meshPtr));
    return *meshes.back();
}

RuntimeValue Mesher::invoke(const std::string& method, const std::vector<RuntimeValue>& args)
{
    if (method == "create_mesh" && args.size() == 5)
    {
        auto retrieved = args[1].as<RuntimeValue::CADObjectPointer>();
        std::cout << "Runtime Error Afer Retrieved" << std::endl;
        Object3d* storedObject = std::dynamic_pointer_cast<Object3d>(retrieved).get();
        create_mesh(*storedObject, args[2].as_number(), args[3].as_number(), args[4].as_number());
        return RuntimeValue{meshes.back()};
    }
    std::cout << "Mesher Args Size " << std::to_string(args.size()) << std::endl;
    throw std::runtime_error("Unknown Mesher method " + method + " with supplied arguments!");
}
