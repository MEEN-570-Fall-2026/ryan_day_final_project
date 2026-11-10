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
        Mesh(std::vector<PointPointers> objectVertices, double elementXSize, double elementYSize, double elementZSize);
        std::vector<TetCubePointers> get_tetrahedra_cubes() const;
        const std::vector<std::shared_ptr<Point>>& get_point_cloud() const;

    private:
        void set_tet_cube_counts();
        void set_object_bounds();
        void set_x_tet_cube_count();
        void set_y_tet_cube_count();
        void set_z_tet_cube_count();
        void create_point_cloud();
        std::size_t get_point_cloud_index(int i, int j, int k) const;
        void create_tetrahedra_cubes();
        std::vector<TetCubePointers> tetCubes;
        std::vector<PointPointers> pointGrid;
        std::vector<PointPointers> objectVertices;
        double elementXSize;
        double elementYSize;
        double elementZSize;
        int xTetCubeCount;
        int yTetCubeCount;
        int zTetCubeCount;
        double objectMinX;
        double objectMaxX;
        double objectMinY;
        double objectMaxY;
        double objectMinZ;
        double objectMaxZ;
};

#endif