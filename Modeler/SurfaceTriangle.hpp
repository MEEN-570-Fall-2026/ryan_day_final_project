#ifndef SURFACETRIANGLE
#define SURFACETRIANGLE

#include "Point.hpp"
#include <array>

class SurfaceTriangle{
public:
    SurfaceTriangle(Point vertex1, Point vertex2, Point vertex3);
    std::array<Point, 3> get_vertices();

private:
    std::array<Point, 3> vertices;

};

#endif