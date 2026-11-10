#include "Tetrahedron.hpp"

Tetrahedron::Tetrahedron(std::vector<PointPtr> vertices) : vertices{vertices}
{
    set_vertex_connections();
}

void Tetrahedron::set_vertex_connections()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertexConnections[i] = {};
        for (int j = 0; j < vertices.size(); j++)
        {
            if (j != i)
            {
                vertexConnections[i].push_back(j);
            }
        }
        
    }
}
