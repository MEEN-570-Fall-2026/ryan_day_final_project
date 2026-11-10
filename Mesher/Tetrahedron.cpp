#include "Tetrahedron.hpp"

Tetrahedron::Tetrahedron(std::vector<Point> vertices) : vertices{vertices}
{
}

void Tetrahedron::set_point_connections()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        pointConnections[i] = {};
        for (int j = 0; j < vertices.size(); j++)
        {
            if (j != i)
            {
                pointConnections[i].push_back(j);
            }
        }
        
    }
}
