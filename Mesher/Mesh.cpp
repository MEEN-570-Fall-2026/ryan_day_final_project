#include "Mesh.hpp"
#include <unordered_set>

Mesh::Mesh(Object3d& object, double elementLength, double elementWidth, double elementHeight) : 
    rawObject{object},
    elementLength{elementLength},
    elementWidth{elementWidth},
    elementHeight{elementHeight}
{
}

void Mesh::build_grid()
{
    Cube centralCube = Cube(rawObject.get_centroid(), 1, 1, 1);
    meshGrid.push_back(centralCube);
}

void Mesh::build_tets_from_grid_element(Cube& gridElement)
{
    std::vector<Point> elementVertices = gridElement.get_vertices();
    
}
