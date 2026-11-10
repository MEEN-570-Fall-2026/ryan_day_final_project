#include "TetrahedraCube.hpp"
#include <algorithm>
#include <array>


TetrahedraCube::TetrahedraCube(std::vector<std::shared_ptr<Point>> vertices) : vertices{vertices}
{
    build_tetrahedra();
}

std::vector<Tetrahedron> TetrahedraCube::get_tetrahedra()
{
    return tetrahedra;
}

std::size_t TetrahedraCube::get_corner_index(const std::vector<int>& xyz)
{
    return xyz[0] + 2 * xyz[1] + 4 * xyz[2];
}

void TetrahedraCube::build_tetrahedra()
{
    std::vector<int> axes = {0, 1, 2};
    do
    {
        std::array<PointPtr, 4> tetPoints;
        std::vector<int> xyz{0, 0, 0};
        tetPoints[0] = vertices[get_corner_index(xyz)];
        for (std::size_t step = 0; step < axes.size(); ++step)
        {
            xyz[axes[step]] = 1;
            tetPoints[step + 1] = vertices[get_corner_index(xyz)];
        }
        tetrahedra.push_back(Tetrahedron(std::vector<PointPtr>{
                tetPoints[0], tetPoints[1],
                tetPoints[2], tetPoints[3]
            }
        ));
    }
    while (std::next_permutation(axes.begin(), axes.end()));
}
