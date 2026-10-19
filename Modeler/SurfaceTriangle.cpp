#include "SurfaceTriangle.hpp"

SurfaceTriangle::SurfaceTriangle(Point vertex1, Point vertex2, Point vertex3) : vertices{vertex1, vertex2, vertex3}
{
}

std::array<Point, 3> SurfaceTriangle::getVertices()
{
    return vertices;
}
