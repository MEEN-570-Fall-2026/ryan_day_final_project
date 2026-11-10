#ifndef TETRAHEDRON
#define TETRAHEDRON

#include <vector>
#include <unordered_map>
#include <memory>
#include "Point.hpp"

class Tetrahedron
{
    using PointPtr = std::shared_ptr<Point>;

    public:
        Tetrahedron(std::vector<PointPtr> vertices);
        std::vector<std::shared_ptr<Point>> get_vertex_connections(int vertex_index);

    private:
        std::vector<PointPtr> vertices;
        void set_vertex_connections();
        std::unordered_map<int, std::vector<int>> vertexConnections;

};

#endif