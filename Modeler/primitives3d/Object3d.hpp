#ifndef OBJECT3D
#define OBJECT3D

#include "Point.hpp"
#include <set>

class Object3d {
public:
    std::set<Point> get_vertices();
    void translate(double xDistance, double yDistance, double zDistance);

protected:
    Point centroid;
    std::set<Point> vertices;
    virtual void set_vertices() = 0;
};

#endif