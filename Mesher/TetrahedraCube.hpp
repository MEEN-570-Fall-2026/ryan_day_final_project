#ifndef TETRAHEDRACUBE
#define TETRAHEDRACUBE

#include <memory>
#include <vector>
#include "Point.hpp"
#include "Tetrahedron.hpp"


class TetrahedraCube {
    using PointPtr = std::shared_ptr<Point>;

    public:
        TetrahedraCube(std::vector<PointPtr> vertices);

    private:
        std::size_t get_corner_index(const std::vector<int>& xyz);
        void build_tetrahedra();

        std::vector<std::shared_ptr<Point>> vertices;
        std::vector<Tetrahedron> tetrahedra;


};

#endif