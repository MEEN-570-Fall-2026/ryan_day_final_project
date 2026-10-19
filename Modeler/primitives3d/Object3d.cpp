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
