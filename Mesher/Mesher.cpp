#include "Mesher.hpp"
#include "Mesh.hpp"
#include "Point.hpp"
#include <memory>

Mesh& Mesher::create_mesh(Object3d& geometry, int element_length, int element_width, int element_height)
{
    std::vector<Point> geometry_vertices = geometry.get_vertices();
    std::vector<std::shared_ptr<Point>> vertexPointers;
    for (Point& vertex : geometry_vertices)
    {
        vertexPointers.push_back(std::make_shared<Point>(vertex));
    }
    MeshPointer meshPtr = std::make_unique<Mesh>(std::move(vertexPointers), element_length, element_width, element_height);
    meshes.push_back(std::move(meshPtr));
    return *meshes.back();
}