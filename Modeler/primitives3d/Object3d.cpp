#include "Object3d.hpp"

std::vector<Point> Object3d::get_vertices()
{
    return vertices;
}

void Object3d::translate(double xDistance, double yDistance, double zDistance)
{
    centroid = Point(
        centroid.x() + xDistance,
        centroid.y() + yDistance,
        centroid.z() + zDistance
    );
    std::vector<Point> newVertices;
    for (Point vertex : vertices)
    {
        newVertices.push_back(
            Point(vertex.x() + xDistance, vertex.y() + yDistance, vertex.z() + zDistance)
        );
    }
    vertices = newVertices;
}

std::vector<SurfaceTriangle> Object3d::getSurfaceTriangles()
{
    return surfaceTriangles;
}

std::vector<std::array<int, 3>> Object3d::getSurfaceTriangleIndices()
{
    return surfaceTriangleIndices;
}

Point Object3d::get_centroid()
{
    return centroid;
}

bool Object3d::operator==(const Object3d& other) const
{
    return (vertices == other.vertices && centroid == other.centroid);
}

RuntimeValue Object3d::invoke(const std::string &method, const std::vector<RuntimeValue> &args)
{
    if (method == "translate" && args.size() == 3)
    {
        translate(args[0].as_number(), args[1].as_number(), args[2].as_number());
        return RuntimeValue{};
    }
    throw std::runtime_error("Unknown method " + method + " with supplied arguments!");
}

void Object3d::set_surface_triangles()
{
    surfaceTriangles.clear();
    for (std::array<int, 3> indices : surfaceTriangleIndices) 
    {
        surfaceTriangles.push_back(
            SurfaceTriangle(
                vertices[indices[0]],
                vertices[indices[1]],
                vertices[indices[2]]
            )
        );
    }
}
