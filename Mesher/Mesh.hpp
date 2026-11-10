#ifndef MESH
#define MESH

#include "Point.hpp"
#include "primitives3d/Object3d.hpp"
#include "primitives3d/Cube.hpp"
#include "TetrahedraCube.hpp"
#include <vector>

class Mesh{
    using PointPointers = std::shared_ptr<Point>;
    using TetCubePointers = std::shared_ptr<TetrahedraCube>;

    public:
        Mesh(std::vector<PointPointers> objectVertices, double elementX, double elementY, double elementZ);
        std::vector<TetCubePointers> get_tetrahedra_cubes();

    private:
        void create_point_cloud();
        void create_tetrahedra_cubes();
        std::vector<TetCubePointers> tetCubes;
        std::vector<PointPointers> pointGrid;
        std::vector<PointPointers> objectVertices;
        double elementX;
        double elementY;
        double elementZ;
        

};

#endif