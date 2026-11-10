#ifndef MESH
#define MESH

#include "Point.hpp"
#include "primitives3d/Object3d.hpp"
#include "primitives3d/Cube.hpp"
#include <vector>

class Mesh{
    public:
        Mesh(Object3d& object, double elementLength, double elementWidth, double elementHeight);

    private:
        void build_grid();
        void build_tets_from_grid_element(Cube& gridElement);

        std::vector<Cube> meshGrid;
        Object3d& rawObject;
        double elementLength;
        double elementWidth;
        double elementHeight;

};

#endif