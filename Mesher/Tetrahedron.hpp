#ifndef TETRAHEDRON
#define TETRAHEDRON

#include <vector>
#include <unordered_map>
#include <memory>
#include "Point.hpp"
#include <Eigen/Dense>


class Tetrahedron
{
    using PointPtr = std::shared_ptr<Point>;

    public:
        Tetrahedron(std::vector<PointPtr> vertices);
        std::vector<std::shared_ptr<Point>> get_vertex_connections(int vertex_index);
        std::vector<std::shared_ptr<Point>> get_vertices() const;
        bool contains(Point& point);

    private:
        std::vector<PointPtr> vertices;
        void set_vertex_connections();
        std::unordered_map<int, std::vector<int>> vertexConnections;
        std::vector<double> compute_barycentric(Point& nonVertexPoint);
        Eigen::Vector3d point_to_eigen(Point& point);

};

#endif