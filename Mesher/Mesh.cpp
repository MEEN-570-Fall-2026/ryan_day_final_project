#include "Mesh.hpp"

Mesh::Mesh(std::vector<PointPointers> objectVertices, double elementX, double elementY, double elementZ) :
    objectVertices{objectVertices},
    elementX{elementX},
    elementY{elementY},
    elementZ{elementZ}
{
    create_point_cloud();
    create_tetrahedra_cubes();
}

std::vector<std::shared_ptr<TetrahedraCube>> Mesh::get_tetrahedra_cubes()
{
    return tetCubes;
}

void Mesh::create_point_cloud()
{
    pointGrid = objectVertices;
}

void Mesh::create_tetrahedra_cubes()
{
    tetCubes.push_back(std::make_shared<TetrahedraCube>(pointGrid));
}
