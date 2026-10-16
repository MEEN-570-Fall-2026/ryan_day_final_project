#include "Object3d.hpp"

std::set<Point> Object3d::get_vertices()
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
    std::set<Point> newVertices;
    for (Point vertex : vertices)
    {
        newVertices.insert(
            Point(vertex.x() + xDistance, vertex.y() + yDistance, vertex.z() + zDistance)
        );
    }
    vertices = newVertices;
}
