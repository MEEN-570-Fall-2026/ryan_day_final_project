#ifndef CUBE
#define CUBE

#include "Object3d.hpp"

class Cube : public Object3d {
public:
    Cube(double xLength, double yLength, double zLength);
    Cube(Point centroidLocation, double xLength, double yLength, double zLength);

private:
    double xLength;
    double yLength;
    double zLength;

    void set_vertices();

};

#endif