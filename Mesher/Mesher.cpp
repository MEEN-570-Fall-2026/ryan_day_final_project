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