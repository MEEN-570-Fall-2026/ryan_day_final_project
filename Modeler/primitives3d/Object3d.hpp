#ifndef OBJECT3D
#define OBJECT3D

#include "Point.hpp"
#include <vector>

class Object3d {
public:
    std::vector<Point> get_vertices();
    void translate(double xDistance, double yDistance, double zDistance);

protected:
    Point centroid;
    std::vector<Point> vertices;
    virtual void set_vertices() = 0;
};

#endif