#include "Tetrahedron.hpp"
#include "DegenerateTetrahedronException.hpp"

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

std::vector<std::shared_ptr<Point>> Tetrahedron::get_vertices() const
{
    return vertices;
}

bool Tetrahedron::contains(Point& point)
{
    std::vector<double> barycentric = compute_barycentric(point);
    for (double lambda : barycentric)
    {
        if (lambda < 0 || lambda > 1)
        {
            return false;
        }
    }
    return true;
}

std::vector<double> Tetrahedron::compute_barycentric(Point& nonVertexPoint)
{
    Eigen::Matrix3d tetDistanceMatrix;
    Eigen::Vector3d intialVertexVector = point_to_eigen(*vertices[0]);
    for (int i = 1; i < vertices.size(); i++)
    {
        tetDistanceMatrix.col(i-1) = point_to_eigen(*vertices[i]) - intialVertexVector;
    }
    Eigen::Vector3d pointLocationVector = point_to_eigen(nonVertexPoint) - intialVertexVector;
    Eigen::FullPivLU<Eigen::Matrix3d> luFactorization(tetDistanceMatrix);
    if (!luFactorization.isInvertible()) {
        throw DegenerateTetrahedronException("Degenerate Tetrahedron Detected!");
    }
    Eigen::Vector3d lambda123 = luFactorization.solve(pointLocationVector);
    double lambda0 = 1.0 - lambda123.sum();
    return std::vector<double> {lambda0, lambda123(0), lambda123(1), lambda123(2)};
}

Eigen::Vector3d Tetrahedron::point_to_eigen(Point& point)
{
    return Eigen::Vector3d(point.x(), point.y(), point.z());
}