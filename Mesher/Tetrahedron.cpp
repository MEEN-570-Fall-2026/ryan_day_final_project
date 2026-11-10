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

std::vector<std::shared_ptr<Point>> Tetrahedron::get_vertex_connections(int vertex_index)
{
    std::vector<int> connectionIndices = vertexConnections[vertex_index];
    std::vector<PointPtr> connectionPtrs;
    for (int index : connectionIndices)
    {
        connectionPtrs.push_back(vertices[index]);
    }
    return connectionPtrs;
}

std::vector<std::shared_ptr<Point>> Tetrahedron::get_vertices()
{
    return vertices;
}
