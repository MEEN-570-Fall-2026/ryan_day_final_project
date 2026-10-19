#ifndef SURFACETRIANGLE
#define SURFACETRIANGLE

#include "Point.hpp"
#include <array>

class SurfaceTriangle{
public:
    SurfaceTriangle(Point vertex1, Point vertex2, Point vertex3);
    std::array<Point, 3> getVertices();

private:
    std::array<Point, 3> vertices;

};

#endif