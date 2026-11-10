#include "Mesher.hpp"
#include "Mesh.hpp"
#include "Point.hpp"
#include <memory>

Mesh& Mesher::create_mesh(Object3d& geometry, double elementSizeX, double elementSizeY, double elementSizeZ)
{
    std::vector<Point> geometry_vertices = geometry.get_vertices();
    std::vector<std::shared_ptr<Point>> vertexPointers;
    for (Point& vertex : geometry_vertices)
    {
        vertexPointers.push_back(std::make_shared<Point>(vertex));
    }
    MeshPointer meshPtr = std::make_unique<Mesh>(std::move(vertexPointers), elementSizeX, elementSizeY, elementSizeZ);
    meshes.push_back(std::move(meshPtr));
    return *meshes.back();
}

RuntimeValue Mesher::invoke(const std::string& method, const std::vector<RuntimeValue>& args)
{
    if (method == "create_mesh" && args.size() == 4)
    {
        auto retrieved = args[0].as<RuntimeValue::CADObjectPointer>();
        Object3d* storedObject = std::dynamic_pointer_cast<Object3d>(retrieved).get();
        create_mesh(*storedObject, args[1].as_number(), args[2].as_number(), args[3].as_number());
        return RuntimeValue{};
    }
    throw std::runtime_error("Unknown method " + method + " with supplied arguments!");
}
