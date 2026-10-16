#ifndef CUBE
#define CUBE

#include "Object3d.hpp"

class Cube : public Object3d {
public:
    Cube(double x_length, double y_length, double z_length);

private:
    double x_length;
    double y_length;
    double z_length;

    void set_vertices();

};

#endif